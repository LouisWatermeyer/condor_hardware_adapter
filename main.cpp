#include <QApplication>
#include <QHostAddress>
#include "ui/mainwindow.h"

#include "logservice/LogService.h"
#include "udpservice/UDPService.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;

    // Start log service
    QObject::connect(LogService::instance(), &LogService::signalNewLogAdded, &w, &Widget::slotNewLogMessage);
    LogService::log("App started", LogService::Info);

    // Start UPD Service
    UDPService udpService(QHostAddress::LocalHost, 55278);
    w.registerUDPService(&udpService);

    // Start COM Service
    COMService comService;
    comService.registerUDPService(&udpService);
    w.registerCOMService(&comService);

    w.show();
    return a.exec();
}
