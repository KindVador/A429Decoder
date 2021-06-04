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

private:
    Ui::A429BnrWidget *ui;
};

