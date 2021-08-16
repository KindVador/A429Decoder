#include "arinc429widget.hpp"
#include "ui_arinc429widget.h"
#include <QObject>
#include <QDebug>
#include <QException>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QList>
#include <QCheckBox>

Arinc429Widget::Arinc429Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Arinc429Widget)
{
    ui->setupUi(this);
    setWindowTitle("ARINC 429 Word Decoder Widget");

    // init of the main block
    ui->lineEdit->setText("");
    ui->lineEdit->setMaxLength(8);  // set the maximum length of lineEdit (Hexadecimal input value) to 8 hexadecimal characters
    ui->lineEdit->setInputMask("HHHHHHHH");

    // init of the DW block
    dwWidget = ui->DwWidget->getUi();

    // init of the BNR block
    bnrWidget = ui->BnrWidget->getUi();
    bnrWidget->bnr_msb_spin_box->setValue(28);
    bnrWidget->bnr_msb_spin_box->setMaximum(32);
    bnrWidget->bnr_msb_spin_box->setMinimum(9);
    bnrWidget->bnr_lsb_spin_box->setValue(11);
    bnrWidget->bnr_lsb_spin_box->setMaximum(32);
    bnrWidget->bnr_lsb_spin_box->setMinimum(9);
    bnrWidget->bnr_resolution_spin_box->setValue(1.0);
    bnrWidget->bnr_resolution_spin_box->setDecimals(10);

    // make connections
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(inputValueChanged(QString)));
    connect(ui->label_msb_first_checkbox, SIGNAL(stateChanged(int)), this, SLOT(labelMsbFirstChanged(int)));
    connect(ui->oddParityCheckBox, SIGNAL(stateChanged(int)), this, SLOT(internalParityTypeChanged(int)));

    // DW block
    for (int i = 1; i < 33; ++i) {
        connect(getPushButtonForBit(i), &QPushButton::clicked, this, [=](){ qDebug() << "--> SIGNAL dwBitClicked(" << i << ")"; emit this->dwBitClicked(i); });
    }

    // BNR block
    connect(bnrWidget->bnr_msb_spin_box, SIGNAL(valueChanged(int)), this, SLOT(updateBnrDefinition()));
    connect(bnrWidget->bnr_lsb_spin_box, SIGNAL(valueChanged(int)), this, SLOT(updateBnrDefinition()));
    connect(bnrWidget->bnr_resolution_spin_box, SIGNAL(valueChanged(double)), this, SLOT(updateBnrDefinition()));
    connect(bnrWidget->bnr_range_spin_box, SIGNAL(valueChanged(double)), this, SLOT(updateBnrDefinition()));
    connect(bnrWidget->signed_check_box, SIGNAL(stateChanged(int)), this, SLOT(updateBnrDefinition()));
    connect(bnrWidget->bnr_msb_spin_box, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){qDebug() << "--> SIGNAL bnrMsbChanged(" << value << ")"; emit bnrMsbChanged(value); });
    connect(bnrWidget->bnr_lsb_spin_box, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){qDebug() << "--> SIGNAL bnrLsbChanged(" << value << ")"; emit bnrLsbChanged(value); });
    connect(bnrWidget->bnr_resolution_spin_box, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=](double value){qDebug() << "--> SIGNAL bnrResolutionChanged(" << value << ")"; emit bnrResolutionChanged(value); });
    connect(bnrWidget->bnr_range_spin_box, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=](double value){qDebug() << "--> SIGNAL bnrRangeChanged(" << value << ")"; emit bnrRangeChanged(value); });
    connect(bnrWidget->signed_check_box, &QCheckBox::stateChanged, this, [=](int state){qDebug() << "--> SIGNAL bntIsSignedChnaged(" << state << ")"; emit bnrIsSignedChanged(state); });
}

Arinc429Widget::~Arinc429Widget()
{
    delete ui;
}

void Arinc429Widget::setRawValue(const QString strValue)
{
    ui->lineEdit->setText(strValue);
}

void Arinc429Widget::setLabelValue(const QString strValue)
{
    // update the main block
    ui->LabelValue->setText(strValue);
    // update the DW block
    if (ui->label_msb_first_checkbox->isChecked()) {
        ui->DwWidget->setFirstLabelDigit(strValue[0].toUpper());
        ui->DwWidget->setSecondLabelDigit(strValue[1].toUpper());
        ui->DwWidget->setThirdLabelDigit(strValue[2].toUpper());
    } else {
        ui->DwWidget->setFirstLabelDigit(strValue[2].toUpper());
        ui->DwWidget->setSecondLabelDigit(strValue[1].toUpper());
        ui->DwWidget->setThirdLabelDigit(strValue[0].toUpper());
    }
}

void Arinc429Widget::setSdiValue(const QString strValue)
{
    // update the main block
    ui->SDIValue->setText(strValue);
    // update the DW block
    ui->DwWidget->setSdiValue(strValue);
}

void Arinc429Widget::setPayloadValue(const QString strValue)
{
    // update the DW block
    ui->DwWidget->setPayloadValue(strValue);
}

void Arinc429Widget::setSsmValue(const QString strValue)
{
    // update the main block
    ui->SSMValue->setText(strValue);
    // update the DW block
    ui->DwWidget->setSsmValue(strValue);
}

void Arinc429Widget::setParityValue(const QString strValue)
{
    // update the main block
    ui->ParityValue->setText(strValue);
    // update the DW block
    ui->DwWidget->setParityValue(strValue);
}

QPushButton *Arinc429Widget::getTextFieldForBit(const int i)
{
     if (i < 0 || i > 32)
         throw QException();

     QString objName = QString("dw_bit%1").arg(i, 2, 10, QChar('0'));
     return this->findChild<QPushButton *>(objName);
}

unsigned int Arinc429Widget::getBnrMsbPosition()
{
    return bnrWidget->bnr_msb_spin_box->value();
}

unsigned int Arinc429Widget::getBnrLsbPosition()
{
    return bnrWidget->bnr_lsb_spin_box->value();
}

double Arinc429Widget::getBnrResolution()
{
    return bnrWidget->bnr_resolution_spin_box->value();
}

bool Arinc429Widget::getBnrIsSigned()
{
    return bnrWidget->signed_check_box->isChecked();
}

void Arinc429Widget::setBnrResolutionValue(const double newValue)
{
    bnrWidget->bnr_resolution_spin_box->setValue(newValue);
}

void Arinc429Widget::setBnrRangeValue(const double newValue)
{
    bnrWidget->bnr_range_spin_box->setValue(newValue);
}

double Arinc429Widget::getBnrRangeValue()
{
    return bnrWidget->bnr_range_spin_box->value();
}

void Arinc429Widget::displayBnrValue(const double value)
{
    bnrWidget->bnr_industrial_value_lcd->display(value);
}

QPushButton *Arinc429Widget::getPushButtonForBit(const int bitNumber)
{
    QString buttonName = QString("dw_bit%1").arg(bitNumber, 2, 10, QChar('0'));
    QPushButton *button = this->findChild<QPushButton *>(buttonName);
    return button;
}

void Arinc429Widget::showDwBlock(const bool &state)
{
    ui->labelDW->setVisible(state);
    ui->DwWidget->setVisible(state);
    ui->lineUnderDw->setVisible(state);
}

void Arinc429Widget::showBnrBlock(const bool &state)
{
    ui->labelBNR->setVisible(state);
    ui->BnrWidget->setVisible(state);
    ui->lineUnderBnr->setVisible(state);
}

void Arinc429Widget::showBcdBlock(const bool &state)
{
    ui->labelBCD->setVisible(state);
    ui->BcdWidget->setVisible(state);
//    ui->lineUnderBcd->setVisible(state);
}

void Arinc429Widget::parityValidity(const bool& isValid)
{
    if (isValid) {
        ui->lblParity->setStyleSheet("QLabel { color : green;}");
        ui->ParityValue->setStyleSheet("QLabel { color : green;}");
    } else {
        ui->lblParity->setStyleSheet("QLabel { color : red;}");
        ui->ParityValue->setStyleSheet("QLabel { color : red;}");
    }
    // update DW block
    ui->DwWidget->parityValidity(isValid);
}

void Arinc429Widget::internalParityTypeChanged(const int &state)
{
    qDebug() << "--> SIGNAL internalParityTypeChanged(" << state << ")";
    emit parityTypeChanged(state);
}

void Arinc429Widget::inputValueChanged(const QString &newValue)
{
    qDebug() << "--> SIGNAL rawValueChanged(" << newValue << ")";
    emit rawValueChanged(newValue);
}

void Arinc429Widget::labelMsbFirstChanged(const int& state)
{
    ui->DwWidget->swapLabelDigits();
    qDebug() << "--> SIGNAL labelNumberMsbFirstChanged(" << state << ")";
    emit labelNumberMsbFirstChanged(state);
}

void Arinc429Widget::updateBnrDefinition()
{
    // update spinboxes limits to avoid MSB < LSB
    bnrWidget->bnr_msb_spin_box->setMinimum(bnrWidget->bnr_lsb_spin_box->value());
    bnrWidget->bnr_lsb_spin_box->setMaximum(bnrWidget->bnr_msb_spin_box->value());
}
