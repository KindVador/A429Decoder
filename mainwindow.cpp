#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <cmath>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("ARINC 429 Word Decoder");
    a429Word = new A429Word();
    adjustSize();

    // make connections
    connect(ui->a429widget, SIGNAL(rawValueChanged(QString)), this, SLOT(valueChangedAction(QString)));
    connect(ui->a429widget, SIGNAL(labelNumberMsbFirstChanged(int)), this, SLOT(labelMsbFirstCheckBoxChanged(int)));
    connect(ui->a429widget, SIGNAL(dwBitClicked(int)), this, SLOT(toggleDwBit(int)));
    connect(ui->a429widget, SIGNAL(bnrMsbChanged(int)), this, SLOT(updateMsbLsbLimits()));
    connect(ui->a429widget, SIGNAL(bnrLsbChanged(int)), this, SLOT(updateMsbLsbLimits()));
    connect(ui->a429widget, SIGNAL(bnrResolutionChanged(double)), this, SLOT(updateBnrRangeValue(double)));
    connect(ui->a429widget, SIGNAL(bnrRangeChanged(double)), this, SLOT(updateBnrResolutionValue(double)));
    connect(ui->a429widget, SIGNAL(bnrIsSignedChanged(int)), this, SLOT(updateBnrIsSignedValue(int)));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAboutWindow()));

    // init raw value
    ui->a429widget->setRawValue(QString("00000000"));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete a429Word;
}

void MainWindow::updateView()
{
    qDebug() << "updateView()";
    QString label = QString::fromStdString(a429Word->getLabelAsOctalString());
    ui->a429widget->setLabelValue(label);
    QString sdi = QString("%1").arg(a429Word->sdi(), 1, 10);
    ui->a429widget->setSdiValue(sdi);
    QString ssm = QString("%1").arg(a429Word->ssm(), 1, 10);
    ui->a429widget->setSsmValue(ssm);
    QString parity = QString("%1").arg(a429Word->parity(), 1, 10);
    ui->a429widget->setParityValue(parity);
    ui->a429widget->parityValidity(a429Word->isParityValid());
    qDebug() << "RAW VALUE: " << a429Word->rawValue() << "LABEL: " << label << "SDI: " << sdi << " SSM: " << ssm << "PARITY: " << parity;

    updateDwBlock();
    updateBnrValue();
}

void MainWindow::updateBnrValue()
{
    qDebug() << "updateBnrValue()";
    double bnrValue = a429Word->getBnrValue(ui->a429widget->getBnrIsSigned(), 29, ui->a429widget->getBnrMsbPosition(), ui->a429widget->getBnrLsbPosition(), ui->a429widget->getBnrResolution());
    qDebug() << "BNR VALUE: " << bnrValue;
    ui->a429widget->displayBnrValue(bnrValue);
}

void MainWindow::showAboutWindow()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("About A429Decoder...");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("version: 2021.1\n\nSource code available at https://github.com/KindVador/A429Decoder\n\nPlease report any issue by opening a PR in the GitHub repository.");
    msgBox.exec();
}

void MainWindow::valueChangedAction(const QString &newValue)
{
    qDebug() << "valueChangedAction(" << newValue << ")";
    a429Word->setRawValue(newValue.toUInt(nullptr, 16));
    qDebug() << "rawValue(): " << a429Word->rawValue();
    updateView();
}

void MainWindow::labelMsbFirstCheckBoxChanged(const int &state)
{
    qDebug() << "labelMsbFirstCheckBoxChanged()";
    a429Word->setLabelNumberMsbFirst(state);
    updateView();
}

void MainWindow::toggleDwBit(const int &bitNumber)
{
    qDebug() << "toggleDwBit()";
    a429Word->toggleBit(bitNumber);
    ui->a429widget->setRawValue(QString("%1").arg(a429Word->rawValue(), 8, 16, QChar('0')).toUpper());
    qDebug() << "TOGGLE BIT: " << bitNumber;
}

void MainWindow::updateDwBlock()
{
    qDebug() << "updateDwBlock()";
    QPushButton* btn;
    for (int i = 1; i < 33; ++i) {
        btn = ui->a429widget->getTextFieldForBit(i);
        QString bitValue = QString("%1").arg(a429Word->getBit(i), 1, 2);
        if (btn)
            btn->setText(bitValue);
    }
}

void MainWindow::updateMsbLsbLimits()
{
    qDebug() << "updateMsbLsbLimits()";
    // updateBnrResolutionValue();
}

void MainWindow::updateBnrRangeValue(const double& resolution)
{
    qDebug() << "updateBnrRangeValue()";
    int exponent = (ui->a429widget->getBnrMsbPosition() - ui->a429widget->getBnrLsbPosition()) + 1;
    double bnrRange = resolution * pow(2, exponent);
    ui->a429widget->setBnrRangeValue(bnrRange);
    updateBnrValue();
}

void MainWindow::updateBnrResolutionValue(const double& bnrRange)
{
    qDebug() << "updateBnrResolutionValue()";
    int exponent = (ui->a429widget->getBnrMsbPosition() - ui->a429widget->getBnrLsbPosition()) + 1;
    double bnrResolution = bnrRange / pow(2, exponent);
    ui->a429widget->setBnrResolutionValue(bnrResolution);
    updateBnrValue();
}

void MainWindow::updateBnrIsSignedValue(const int& state)
{
    qDebug() << "updateBnrIsSignedValue(" << state << ")";
    updateBnrValue();
}
