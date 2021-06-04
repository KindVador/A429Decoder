#include "a429dwwidget.hpp"

A429DwWidget::A429DwWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::A429DwWidget)
{
    ui->setupUi(this);
    ui->gridLayoutDW->setSpacing(0);
    ui->gridLayoutDW->setAlignment(Qt::AlignHCenter);
}

A429DwWidget::~A429DwWidget()
{
    delete ui;
}

void A429DwWidget::setFirstLabelDigit(const QString strValue)
{
    ui->dw_first_label_digit->setText(strValue);
}

void A429DwWidget::setSecondLabelDigit(const QString strValue)
{
    ui->dw_second_label_digit->setText(strValue);
}

void A429DwWidget::setThirdLabelDigit(const QString strValue)
{
    ui->dw_third_label_digit->setText(strValue);
}

void A429DwWidget::setSdiValue(const QString strValue)
{
    ui->dw_sdi_value->setText(strValue);
}

void A429DwWidget::setSsmValue(const int value)
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

void A429DwWidget::setSsmValue(const QString strValue)
{
    setSsmValue(strValue.toInt());
}

void A429DwWidget::setParityValue(const int value)
{
    if (value) {
        ui->dw_parity_value->setText("1");
    } else {
        ui->dw_parity_value->setText("0");
    }
}

void A429DwWidget::setParityValue(const QString strValue)
{
    setParityValue(strValue.toInt());
}

void A429DwWidget::setPayloadValue(const QString strValue)
{
    ui->dw_payload_value->setText(strValue);
}

void A429DwWidget::swapLabelDigits()
{
    QString firstDigit = ui->dw_first_label_digit->text();
    ui->dw_first_label_digit->setText(ui->dw_third_label_digit->text());
    ui->dw_third_label_digit->setText(firstDigit);
    // TO DO: ADAPT POSITION OF QLABELS
}

void A429DwWidget::parityValidity(const bool& isValid)
{
    if (isValid) {
        ui->dw_parity_value->setStyleSheet("QLabel { color : green;}");
    } else {
        ui->dw_parity_value->setStyleSheet("QLabel { color : red;}");
    }
}

Ui::A429DwWidget *A429DwWidget::getUi() const
{
    return ui;
}
