#include "a429bnrwidget.hpp"
#include "ui_a429bnrwidget.h"

A429BnrWidget::A429BnrWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::A429BnrWidget)
{
    ui->setupUi(this);
}

A429BnrWidget::~A429BnrWidget()
{
    delete ui;
}

Ui::A429BnrWidget *A429BnrWidget::getUi() const
{
    return ui;
}
