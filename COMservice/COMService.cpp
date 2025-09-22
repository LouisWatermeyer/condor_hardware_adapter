#include "COMService.h"
#include "LogService.h"

#include <string>
#include <Windows.h>
#include <QComboBox>
#include <QSerialPort>
#include <QSharedPointer>

COMService::COMService(QObject *parent) : QObject(parent), mSerialPort(nullptr)
{
    // Initialize serial port
    mSerialPort = new QSerialPort(this);

    // Open COM device on startup
    changeCOM();
}

void COMService::registerUDPService(UDPService *service)
{
    connect(service, &UDPService::signalDatagramProcessed, this, &COMService::slotSendMessage);
}

void COMService::slotComSelectorIndexChanged(int index)
{
    // The sender must be a combobox
    QComboBox *senderCB = qobject_cast<QComboBox *>(sender());
    if (!senderCB)
        return;

    mCurrentCOMName = senderCB->itemText(index).split(" ").first();

    LogService::log("Changed COM to " + mCurrentCOMName, LogService::Info);

    changeCOM();
}

void COMService::changeCOM()
{
    // Close existing connection if open
    closeCOMDevice();

    // Open new COM device
    openCOMDevice();
}

void COMService::openCOMDevice()
{
    if (!mSerialPort)
        return;

    // If no COM name is set, try to find the first available port
    if (mCurrentCOMName.isEmpty())
    {
        QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
        if (!availablePorts.isEmpty())
        {
            mCurrentCOMName = availablePorts.first().portName();
            LogService::log("No COM port specified, using first available: " + mCurrentCOMName, LogService::Info);
        }
        else
        {
            LogService::log("No COM ports available", LogService::Warning);
            return;
        }
    }

    // Set port name
    mSerialPort->setPortName(mCurrentCOMName);

    // Configure serial port settings
    mSerialPort->setBaudRate(QSerialPort::Baud9600);
    mSerialPort->setDataBits(QSerialPort::Data8);
    mSerialPort->setParity(QSerialPort::NoParity);
    mSerialPort->setStopBits(QSerialPort::OneStop);
    mSerialPort->setFlowControl(QSerialPort::NoFlowControl);

    // Attempt to open the port
    if (mSerialPort->open(QIODevice::ReadWrite))
    {
        LogService::log("Successfully opened COM port: " + mCurrentCOMName, LogService::Info);
    }
    else
    {
        LogService::log("Failed to open COM port " + mCurrentCOMName + ": " + mSerialPort->errorString(), LogService::Error);
    }
}

void COMService::closeCOMDevice()
{
    if (mSerialPort && mSerialPort->isOpen())
    {
        LogService::log("Closing COM port: " + mSerialPort->portName(), LogService::Info);
        mSerialPort->close();
    }
}

void COMService::slotSendMessage(QSharedPointer<QMap<QString, double>> data)
{
    // Check if data pointer is valid
    if (!data)
    {
        LogService::log("Received null data pointer in slotSendMessage", LogService::Warning);
        return;
    }

    // airspeed = spd; altitude = alt; vario = var; gforce = g
    // JSON Format: {spd: double, alt: double, var: double, g: double}
    QString message = "{\"spd\": " + QString::number(data->value("airspeed")) + ", \"alt\": " + QString::number(data->value("altitude")) + ", \"var\": " + QString::number(data->value("vario")) + ", \"g\": " + QString::number(data->value("gforce")) + "}";

    if (mSerialPort && mSerialPort->isOpen())
    {
        mSerialPort->write(message.toUtf8());
        LogService::log("Sent message to COM port: " + message, LogService::Debug);
    }
    else
    {
        LogService::log("Failed to write to COM port " + mCurrentCOMName + ": Port not open or invalid", LogService::Error);
    }
}