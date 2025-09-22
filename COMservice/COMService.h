#ifndef COMSERVICE_H
#define COMSERVICE_H

#include <QObject>
#include <QMap>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QSharedPointer>
#include "UDPService.h"

class COMService : public QObject
{
    Q_OBJECT

public:
    COMService(QObject *parent = nullptr);

    void registerUDPService(UDPService *service);

public slots:
    void slotComSelectorIndexChanged(int index);
    void slotSendMessage(QSharedPointer<QMap<QString, double>> data);

private:
    void changeCOM();
    void openCOMDevice();
    void closeCOMDevice();

    QString mCurrentCOMName;
    QSerialPort *mSerialPort;
};

#endif // COMSERVICE_H
