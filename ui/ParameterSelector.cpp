#include "ParameterSelector.h"

#include <QHBoxLayout>

ParameterSelector::ParameterSelector(QWidget *parent)
    : QFrame{parent}
{
    mNameLabel.setText(objectName());
    mValueLabel.setText("0");

    // Set up layout
    QHBoxLayout *tLayout = new QHBoxLayout(this);
    tLayout->addWidget(&mNameLabel);
    tLayout->addStretch();
    tLayout->addWidget(&mValueLabel);
    tLayout->addWidget(&mCheckBox);
    setLayout(tLayout);

    setFrameStyle(Box);
    setFrameShadow(Plain);
}

void ParameterSelector::setDisplayName(QString name)
{
    mNameLabel.setText(name);
}

void ParameterSelector::slotUpdateValue(QSharedPointer<QMap<QString, double>> newValues)
{
    mValueLabel.setText(QString::number(newValues.data()->value(mNameLabel.text())));
}
