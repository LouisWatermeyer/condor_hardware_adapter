#include "mainwindow.h"
#include "ui_mainwindow.h"

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
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotNewLogMessage(QString message)
{
    ui->logDisplay->setPlainText(ui->logDisplay->toPlainText() + message);
}
