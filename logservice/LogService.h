#ifndef LOGSERVICE_H
#define LOGSERVICE_H

#include <QObject>
#include <QTimer>

class LogService : public QObject
{
    Q_OBJECT

public:
    enum LogLevel
    {
        Debug,
        Info,
        Warning,
        Error
    };

    LogService(LogService &other) = delete;
    void operator=(const LogService &) = delete;
    ~LogService();

    static LogService *instance();

    static void log(QString message, LogLevel level = Debug);

signals:
    void signalNewLogAdded(QString message);

protected:
    explicit LogService(QObject *parent = nullptr);
    static LogService *instance_;

    void addToLogs(QString formatedMessage);

    QString mLogs;
    QTimer mLogFileTimer;

    const int maxLogFileSize = 10485760; // 10 MiB

protected slots:
    void slotWriteLogFile();
};

#endif // LOGSERVICE_H
