#include <QApplication>
#include "mainwindow.h"

#include "logservice/LogService.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;

    // Start log service
    LogService::log("App started", LogService::Info);

    // Start UPD Service

    w.show();
    return a.exec();
}
