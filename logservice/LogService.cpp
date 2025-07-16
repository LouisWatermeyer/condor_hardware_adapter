#include "LogService.hpp"

#include <QApplication>
#include <QDateTime>
#include <QDir>
#include <QRegularExpression>
#include <ostream>

LogService *LogService::instance_ = nullptr;

LogService::LogService(QObject *parent)
    : QObject{parent}
{
    // Start log file timer
    mLogFileTimer.setInterval(15000);
    connect(&mLogFileTimer, &QTimer::timeout, this, &LogService::slotWriteLogFile);
    mLogFileTimer.start();
}

LogService::~LogService()
{
    // Write logs before shutdown
    slotWriteLogFile();
}

LogService *LogService::instance()
{

    if (instance_ == nullptr)
        instance_ = new LogService();

    return instance_;
}

void LogService::log(QString message, LogLevel level)
{
    QString formated;

    formated.append(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss:zzz"));

    switch (level)
    {
    case Error:
        formated.append("|ERROR  |");
        break;
    case Warning:
        formated.append("|WARNING|");
        break;
    case Info:
        formated.append("|INFO   |");
        break;
    case Debug:
    default:
        formated.append("|DEBUG  |");
        break;
    }

    formated.append(message + '\n');

    instance()->addToLogs(formated);
}

void LogService::addToLogs(QString formatedMessage)
{
    mLogs.append(formatedMessage);
    emit signalNewLogAdded(formatedMessage);
}

void LogService::slotWriteLogFile()
{
    // Only write if we have to
    if (mLogs.isEmpty())
        return;

    QDir dir(QDir::currentPath() + "/logs", "*.log");

    // check if the dir exists -> create it
    if (!dir.exists())
        dir.mkpath(dir.path());

    QStringList logFiles = dir.entryList();

    QString debugMsg = "Found " + QString::number(logFiles.count()) + " logfiles: ";
    for (auto file : logFiles)
        debugMsg.append(file + ", ");
    debugMsg.chop(2);

    log(debugMsg, Debug);

    QFile *logFile;
    // Create a new first file if needed
    if (logFiles.isEmpty())
        logFile = new QFile(QDir::currentPath() + "/logs/logfile_1.log");
    else
        logFile = new QFile(logFiles.last());

    // Check if the chosen file is already too large
    if (logFile->size() >= maxLogFileSize)
    {
        QRegularExpression regex("_(\\d+)\\.log$");
        int maxLogFileNumber = regex.match(logFile->fileName()).captured().toInt();

        delete logFile;
        logFile = new QFile(QString("/logs/logfile_%1.log").arg(maxLogFileNumber + 1));
    }

    // Now we should have a calid file to write.
    if (logFile->open(QIODevice::Append))
    {
        QTextStream out(logFile);
        out << mLogs;
        mLogs.clear();
    }

    if (logFile)
    {
        logFile->close();
        logFile->deleteLater();
    }
}
