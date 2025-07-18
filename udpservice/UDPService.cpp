#include "UDPService.h"
#include "LogService.h"

#include <QSharedPointer>

UDPService::UDPService(QHostAddress host, int port, QObject *parent)
    : mHost(host), mPort(port), QObject{parent}
{
    mProcessedData = QSharedPointer<QMap<QString, QString>>(new QMap<QString, QString>);
    initSocket();
}

UDPService::~UDPService()
{
    mUDPSocket->close();
}

void UDPService::initSocket()
{
    mUDPSocket = new QUdpSocket(this);
    mUDPSocket->bind(mHost, mPort);
    LogService::log("Listening at UDP " + mHost.toString() + ":" + QString::number(mPort));

    connect(mUDPSocket, &QUdpSocket::readyRead,
            this, &UDPService::slotReadPendingDatagrams);
}

void UDPService::slotReadPendingDatagrams()
{
    while (mUDPSocket->hasPendingDatagrams())
    {
        QNetworkDatagram datagram = mUDPSocket->receiveDatagram();
        processDatagram(datagram);
    }
}

void UDPService::processDatagram(QNetworkDatagram datagram)
{
    LogService::log("Datagram recieved:", LogService::LogLevel::Debug);
    LogService::log(datagram.data(), LogService::LogLevel::Debug);

    QStringList parameters = QString(datagram.data()).split('\n');
    for (auto parameter : parameters)
    {
        QStringList keyValue = parameter.split('=');

        if (keyValue.count() == 2)
            mProcessedData.data()->insert(keyValue.first(), keyValue.last());
    }

    emit signalDatagramProcessed(mProcessedData);
}
