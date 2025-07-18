#ifndef UDPSERCIVE_H
#define UDPSERCIVE_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QHostAddress>
#include <QMap>
#include <QSharedPointer>

class UDPService : public QObject
{
    Q_OBJECT

public:
    UDPService(QHostAddress host, int port, QObject *parent = nullptr);
    ~UDPService();

signals:
    void signalDatagramProcessed(QSharedPointer<QMap<QString, QString>> result);

private slots:
    void slotReadPendingDatagrams();

private:
    void initSocket();
    void processDatagram(QNetworkDatagram datagram);

    QUdpSocket *mUDPSocket;
    QHostAddress mHost;
    int mPort;
    QSharedPointer<QMap<QString, QString>> mProcessedData;
};

#endif // UDPSERCIVE_H
