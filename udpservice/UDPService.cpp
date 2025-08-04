#include "UDPService.h"
#include "LogService.h"

#include <QSharedPointer>
#include <QVariantMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDir>

UDPService::UDPService(QHostAddress host, int port, QObject *parent)
    : mHost(host), mPort(port), QObject{parent}
{
    mProcessedData = QSharedPointer<QMap<QString, double>>(new QMap<QString, double>);
    initSocket();
    lastDatagramTime = timeObject.msecsSinceStartOfDay();
}

UDPService::~UDPService()
{
    mUDPSocket->close();
    QJsonDocument doc;
    doc.setArray(testData);
    QFile *testFile = new QFile(QDir::currentPath() + "/testFile.json", this);

    if (testFile->open(QIODevice::ReadWrite))
    {
        QTextStream out(testFile);
        out << doc.toJson();
        testFile->close();
    }
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
            mProcessedData.data()->insert(keyValue.first(), keyValue.last().toDouble());
    }

    // Save to test File
    mProcessedData.data()->insert("timeSinceLastDatagram", timeObject.msecsSinceStartOfDay() - lastDatagramTime);
    lastDatagramTime = timeObject.msecsSinceStartOfDay();

    QVariantMap vmap;
    QMapIterator<QString, double> i(*mProcessedData.data());
    while (i.hasNext())
    {
        i.next();
        vmap.insert(i.key(), i.value());
    }
    testData.append(QJsonObject::fromVariantMap(vmap));

    emit signalDatagramProcessed(mProcessedData);
}
