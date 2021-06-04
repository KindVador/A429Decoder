#pragma once

#include <QWidget>
#include <QSpinBox>
#include "ui_a429bnrwidget.h"

namespace Ui {
class A429BnrWidget;
}

class A429BnrWidget : public QWidget
{
    Q_OBJECT

public:
    explicit A429BnrWidget(QWidget *parent = nullptr);
    ~A429BnrWidget();

    // GETTERS
    Ui::A429BnrWidget *getUi() const;

    // METHODS
//    void setMsbValue(const int& value);
//    void setLsbValue(const int& value);
//    void setResolutionValue(const double& value);

private:
    Ui::A429BnrWidget *ui;
};

