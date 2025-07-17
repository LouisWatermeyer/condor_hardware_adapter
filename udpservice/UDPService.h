#ifndef UDPSERCIVE_H
#define UDPSERCIVE_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QHostAddress>

class UDPService : public QObject
{
    Q_OBJECT

public:
    UDPService(QHostAddress host, int port, QObject *parent = nullptr);
    ~UDPService();

private slots:
    void slotReadPendingDatagrams();

private:
    void initSocket();
    void processDatagram(QNetworkDatagram datagram);

    QUdpSocket *mUDPSocket;
    QHostAddress mHost;
    int mPort;
};

#endif // UDPSERCIVE_H
