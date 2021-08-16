#include "a429bcdwidget.hpp"
#include "ui_a429bcdwidget.h"

A429BcdWidget::A429BcdWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::A429BcdWidget)
{
    ui->setupUi(this);
}

A429BcdWidget::~A429BcdWidget()
{
    delete ui;
}
