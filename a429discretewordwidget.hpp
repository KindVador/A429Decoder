#pragma once

#include <QWidget>

namespace Ui {
class A429DiscreteWordWidget;
}

class A429DiscreteWordWidget : public QWidget
{
    Q_OBJECT

public:
    explicit A429DiscreteWordWidget(QWidget *parent = nullptr);
    ~A429DiscreteWordWidget();

    //
    void setFirstLabelDigit(const QString strValue);
    void setSecondLabelDigit(const QString strValue);
    void setThirdLabelDigit(const QString strValue);
    void setSdiValue(const QString strValue);
    void setSsmValue(const int value);
    void setSsmValue(const QString strValue);
    void setParityValue(const QString strValue);
    void setPayloadValue(const QString strValue);
    void swapLabelDigits();
    void parityValidity(const bool& isValid);
private:
    Ui::A429DiscreteWordWidget *ui;
};

