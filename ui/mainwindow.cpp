#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ParameterSelector.h"
#include <QTextDocument>
#include <QSerialPortInfo>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Get available COM Ports
    Q_FOREACH (QSerialPortInfo port, QSerialPortInfo::availablePorts())
    {
        ui->comDeviceCBox->addItem(port.portName());
    }

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
    ui->logLevelCBox->setCurrentIndex(1); // Default to Info

    // Setup ParameterSelectors
    ui->speedSelector->setDisplayName("airspeed");
    ui->altitudeSelector->setDisplayName("altitude");
    ui->varioSelector->setDisplayName("vario");
    ui->evarioSelector->setDisplayName("evario");
    ui->nettovarioSelector->setDisplayName("nettovario");
    ui->integratorSelector->setDisplayName("integrator");
    ui->compassSelector->setDisplayName("compass");
    ui->slipballSelector->setDisplayName("slipball");
    ui->turnrateSelector->setDisplayName("turnrate");
    ui->yawstringangleSelector->setDisplayName("yawstringangle");
    ui->radiofrequencySelector->setDisplayName("radiofrequency");
    ui->yawSelector->setDisplayName("yaw");
    ui->pitchSelector->setDisplayName("pitch");
    ui->bankSelector->setDisplayName("bank");
    ui->quaternionxSelector->setDisplayName("quaternionx");
    ui->quaternionySelector->setDisplayName("quaterniony");
    ui->quaternionzSelector->setDisplayName("quaternionz");
    ui->quaternionwSelector->setDisplayName("quaternionw");
    ui->axSelector->setDisplayName("ax");
    ui->aySelector->setDisplayName("ay");
    ui->azSelector->setDisplayName("az");
    ui->vxSelector->setDisplayName("vx");
    ui->vySelector->setDisplayName("vy");
    ui->vzSelector->setDisplayName("vz");
    ui->rollrateSelector->setDisplayName("rollrate");
    ui->pitchrateSelector->setDisplayName("pitchrate");
    ui->yawrateSelector->setDisplayName("yawrate");
    ui->gforceSelector->setDisplayName("gforce");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::registerUDPService(UDPService *service)
{
    if (service == nullptr)
        return;

    mUDPServiceRef = service;

    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->speedSelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->altitudeSelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->varioSelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->evarioSelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->nettovarioSelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->integratorSelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->compassSelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->slipballSelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->turnrateSelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->yawstringangleSelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->radiofrequencySelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->yawSelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->pitchSelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->bankSelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->quaternionxSelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->quaternionySelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->quaternionzSelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->quaternionwSelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->axSelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->aySelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->azSelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->vxSelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->vySelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->vzSelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->rollrateSelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->pitchrateSelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->yawrateSelector, &ParameterSelector::slotUpdateValue);
    connect(mUDPServiceRef, &UDPService::signalDatagramProcessed, ui->gforceSelector, &ParameterSelector::slotUpdateValue);
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

void Widget::registerCOMService(COMService *service)
{
    if (service == nullptr)
        return;

    mCOMServiceRef = service;

    connect(ui->comDeviceCBox, &QComboBox::currentIndexChanged, mCOMServiceRef, &COMService::slotComSelectorIndexChanged);
}
