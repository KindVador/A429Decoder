#pragma once

#include <QWidget>
#include "ui_a429dwwidget.h"

namespace Ui {
class A429DwWidget;
}

class A429DwWidget : public QWidget
{
    Q_OBJECT

public:
    explicit A429DwWidget(QWidget *parent = nullptr);
    ~A429DwWidget();

    // GETTERS
    Ui::A429DwWidget *getUi() const;

    // METHODS
    void setFirstLabelDigit(const QString strValue);
    void setSecondLabelDigit(const QString strValue);
    void setThirdLabelDigit(const QString strValue);
    void setSdiValue(const QString strValue);
    void setSsmValue(const int value);
    void setSsmValue(const QString strValue);
    void setParityValue(const int value);
    void setParityValue(const QString strValue);
    void setPayloadValue(const QString strValue);
    void swapLabelDigits();
    void parityValidity(const bool& isValid);

private:
    Ui::A429DwWidget *ui;
};

