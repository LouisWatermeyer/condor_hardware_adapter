#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../logservice/LogService.h"
#include <QTextDocument>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Set Log output to monoapace
    QTextDocument *doc = ui->logDisplay->document();
    QFont font = doc->defaultFont();
    font.setFamily("Courier New");
    doc->setDefaultFont(font);

    // Setup LogLevel combobox
    ui->logLevelCBox->addItem("Debug", LogService::LogLevel::Debug);
    ui->logLevelCBox->addItem("Info", LogService::LogLevel::Info);
    ui->logLevelCBox->addItem("Warning", LogService::LogLevel::Warning);
    ui->logLevelCBox->addItem("Error", LogService::LogLevel::Error);
    ui->logLevelCBox->setCurrentIndex(0); // Default to Info
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotNewLogMessage(QString message, LogService::LogLevel level)
{
    if (ui->logLevelCBox->currentData().toInt() <= level)
    {
        ui->logDisplay->moveCursor(QTextCursor::End);
        ui->logDisplay->insertPlainText(message);
        ui->logDisplay->moveCursor(QTextCursor::End);
    }
}
