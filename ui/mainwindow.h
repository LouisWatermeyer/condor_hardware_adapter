#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include "LogService.h"
#include "UDPService.h"
#include "COMService.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void registerUDPService(UDPService *service);
    void registerCOMService(COMService *service);

public slots:
    void slotNewLogMessage(QString message, LogService::LogLevel level);

private:
    Ui::Widget *ui;
    LogService::LogLevel mLogLevel = LogService::LogLevel::Info;

    UDPService *mUDPServiceRef = nullptr;
    COMService *mCOMServiceRef = nullptr;
};

#endif // MAINWINDOW_H
