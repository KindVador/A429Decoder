#include "a429discretewordwidget.hpp"
#include "ui_a429dirscretewordwidget.h"

A429DiscreteWordWidget::A429DiscreteWordWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::A429DiscreteWordWidget)
{
    ui->setupUi(this);
    ui->gridLayoutDW->setSpacing(0);
    ui->gridLayoutDW->setAlignment(Qt::AlignHCenter);
}

A429DiscreteWordWidget::~A429DiscreteWordWidget()
{
    delete ui;
}

void A429DiscreteWordWidget::setFirstLabelDigit(const QString strValue)
{
    ui->dw_first_label_digit->setText(strValue);
}

void A429DiscreteWordWidget::setSecondLabelDigit(const QString strValue)
{
    ui->dw_second_label_digit->setText(strValue);
}

void A429DiscreteWordWidget::setThirdLabelDigit(const QString strValue)
{
    ui->dw_third_label_digit->setText(strValue);
}

void A429DiscreteWordWidget::setSdiValue(const QString strValue)
{
    ui->dw_sdi_value->setText(strValue);
}

void A429DiscreteWordWidget::setSsmValue(const int value)
{
    switch (value) {
    case 0:
        ui->dw_ssm_value->setText("NO");
        break;
    case 1:
        ui->dw_ssm_value->setText("NCD");
        break;
    case 2:
        ui->dw_ssm_value->setText("FT");
        break;
    case 3:
        ui->dw_ssm_value->setText("FW");
        break;
    default:
        ui->dw_ssm_value->setText("");
        break;
    }
}

void A429DiscreteWordWidget::setSsmValue(const QString strValue)
{
    setSsmValue(strValue.toInt());
}

void A429DiscreteWordWidget::setParityValue(const int value)
{
    if (value) {
        ui->dw_parity_value->setText("1");
    } else {
        ui->dw_parity_value->setText("0");
    }
}

void A429DiscreteWordWidget::setParityValue(const QString strValue)
{
    setParityValue(strValue.toInt());
}

void A429DiscreteWordWidget::setPayloadValue(const QString strValue)
{
    ui->dw_payload_value->setText(strValue);
}

void A429DiscreteWordWidget::swapLabelDigits()
{
    QString firstDigit = ui->dw_first_label_digit->text();
    ui->dw_first_label_digit->setText(ui->dw_third_label_digit->text());
    ui->dw_third_label_digit->setText(firstDigit);
    // TO DO: ADAPT POSITION OF QLABELS
}

void A429DiscreteWordWidget::parityValidity(const bool& isValid)
{
    if (isValid) {
        ui->dw_parity_value->setStyleSheet("QLabel { color : green;}");
    } else {
        ui->dw_parity_value->setStyleSheet("QLabel { color : red;}");
    }
}
