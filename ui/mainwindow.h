#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include "../logservice/LogService.h"

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

public slots:
    void slotNewLogMessage(QString message, LogService::LogLevel level);

private:
    Ui::Widget *ui;
    LogService::LogLevel mLogLevel = LogService::LogLevel::Info;
};

#endif // MAINWINDOW_H
