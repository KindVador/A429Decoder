#include "arinc429widget.h"
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

    // init of the BNR block
    ui->bnr_msb_spin_box->setValue(28);
    ui->bnr_msb_spin_box->setMaximum(32);
    ui->bnr_msb_spin_box->setMinimum(9);
    ui->bnr_lsb_spin_box->setValue(11);
    ui->bnr_lsb_spin_box->setMaximum(32);
    ui->bnr_lsb_spin_box->setMinimum(9);
    ui->bnr_resolution_spin_box->setValue(1.0);
    ui->bnr_resolution_spin_box->setDecimals(10);

    // make connections
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(inputValueChanged(QString)));
    connect(ui->label_msb_first_checkbox, SIGNAL(stateChanged(int)), this, SLOT(labelMsbFirstChanged(int)));

    // DW block
    for (int i = 1; i < 33; ++i) {
        connect(getPushButtonForBit(i), &QPushButton::clicked, this, [=](){ qDebug() << "--> SIGNAL dwBitClicked(" << i << ")"; emit this->dwBitClicked(i); });
    }

    // BNR block
    connect(ui->bnr_msb_spin_box, SIGNAL(valueChanged(int)), this, SLOT(updateBnrDefinition()));
    connect(ui->bnr_lsb_spin_box, SIGNAL(valueChanged(int)), this, SLOT(updateBnrDefinition()));
    connect(ui->bnr_resolution_spin_box, SIGNAL(valueChanged(double)), this, SLOT(updateBnrDefinition()));
    connect(ui->bnr_range_spin_box, SIGNAL(valueChanged(double)), this, SLOT(updateBnrDefinition()));
    connect(ui->signed_check_box, SIGNAL(stateChanged(int)), this, SLOT(updateBnrDefinition()));
    connect(ui->bnr_msb_spin_box, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){qDebug() << "--> SIGNAL bnrMsbChanged(" << value << ")"; emit bnrMsbChanged(value); });
    connect(ui->bnr_lsb_spin_box, QOverload<int>::of(&QSpinBox::valueChanged), this, [=](int value){qDebug() << "--> SIGNAL bnrLsbChanged(" << value << ")"; emit bnrLsbChanged(value); });
    connect(ui->bnr_resolution_spin_box, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=](double value){qDebug() << "--> SIGNAL bnrResolutionChanged(" << value << ")"; emit bnrResolutionChanged(value); });
    connect(ui->bnr_range_spin_box, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [=](double value){qDebug() << "--> SIGNAL bnrRangeChanged(" << value << ")"; emit bnrRangeChanged(value); });
    connect(ui->signed_check_box, &QCheckBox::stateChanged, this, [=](int state){qDebug() << "--> SIGNAL bntIsSignedChnaged(" << state << ")"; emit bnrIsSignedChanged(state); });
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
        ui->widgetDW->setFirstLabelDigit(strValue[0].toUpper());
        ui->widgetDW->setSecondLabelDigit(strValue[1].toUpper());
        ui->widgetDW->setThirdLabelDigit(strValue[2].toUpper());
    } else {
        ui->widgetDW->setFirstLabelDigit(strValue[2].toUpper());
        ui->widgetDW->setSecondLabelDigit(strValue[1].toUpper());
        ui->widgetDW->setThirdLabelDigit(strValue[0].toUpper());
    }
}

void Arinc429Widget::setSdiValue(const QString strValue)
{
    // update the main block
    ui->SDIValue->setText(strValue);
    // update the DW block
    ui->widgetDW->setSdiValue(strValue);
}

void Arinc429Widget::setPayloadValue(const QString strValue)
{
    // update the DW block
    ui->widgetDW->setPayloadValue(strValue);
}

void Arinc429Widget::setSsmValue(const QString strValue)
{
    // update the main block
    ui->SSMValue->setText(strValue);
    // update the DW block
    ui->widgetDW->setSsmValue(strValue);
}

void Arinc429Widget::setParityValue(const QString strValue)
{
    // update the main block
    ui->ParityValue->setText(strValue);
    // update the DW block
    ui->widgetDW->setParityValue(strValue);
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
    return ui->bnr_msb_spin_box->value();
}

unsigned int Arinc429Widget::getBnrLsbPosition()
{
    return ui->bnr_lsb_spin_box->value();
}

double Arinc429Widget::getBnrResolution()
{
    return ui->bnr_resolution_spin_box->value();
}

bool Arinc429Widget::getBnrIsSigned()
{
    return ui->signed_check_box->isChecked();
}

void Arinc429Widget::setBnrResolutionValue(const double newValue)
{
    ui->bnr_resolution_spin_box->setValue(newValue);
}

void Arinc429Widget::setBnrRangeValue(const double newValue)
{
    ui->bnr_range_spin_box->setValue(newValue);
}

double Arinc429Widget::getBnrRangeValue()
{
    return ui->bnr_range_spin_box->value();
}

void Arinc429Widget::displayBnrValue(const double value)
{
    ui->bnr_industrial_value_lcd->display(value);
}

QPushButton *Arinc429Widget::getPushButtonForBit(const int bitNumber)
{
    QString buttonName = QString("dw_bit%1").arg(bitNumber, 2, 10, QChar('0'));
    QPushButton *button = this->findChild<QPushButton *>(buttonName);
    return button;
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
    ui->widgetDW->parityValidity(isValid);
}

void Arinc429Widget::inputValueChanged(const QString &newValue)
{
    qDebug() << "--> SIGNAL rawValueChanged(" << newValue << ")";
    emit rawValueChanged(newValue);
}

void Arinc429Widget::labelMsbFirstChanged(const int& state)
{
    ui->widgetDW->swapLabelDigits();
    qDebug() << "--> SIGNAL labelNumberMsbFirstChanged(" << state << ")";
    emit labelNumberMsbFirstChanged(state);
}

void Arinc429Widget::updateBnrDefinition()
{
    // update spinboxes limits to avoid MSB < LSB
    ui->bnr_msb_spin_box->setMinimum(ui->bnr_lsb_spin_box->value());
    ui->bnr_lsb_spin_box->setMaximum(ui->bnr_msb_spin_box->value());
}

