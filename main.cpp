#include <QApplication>
#include "ui/mainwindow.h"

#include "logservice/LogService.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;

    // Start log service
    QObject::connect(LogService::instance(), &LogService::signalNewLogAdded, &w, &Widget::slotNewLogMessage);
    LogService::log("App started", LogService::Info);

    // Start UPD Service

    w.show();
    return a.exec();
}
