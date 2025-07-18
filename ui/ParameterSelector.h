#ifndef PARAMETERSELECTOR_H
#define PARAMETERSELECTOR_H

#include <QFrame>
#include <QLabel>
#include <QCheckBox>
#include <QSharedPointer>

class ParameterSelector : public QFrame
{
    Q_OBJECT

public:
    explicit ParameterSelector(QWidget *parent = nullptr);

    void setDisplayName(QString name);

public slots:
    void slotUpdateValue(QSharedPointer<QMap<QString, QString>> newValues);

private:
    QLabel mNameLabel;
    QLabel mValueLabel;
    QCheckBox mCheckBox;
};

#endif // PARAMETERSELECTOR_H
