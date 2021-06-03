#ifndef ARINC429WIDGET_H
#define ARINC429WIDGET_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class Arinc429Widget;
}

class Arinc429Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Arinc429Widget(QWidget *parent = nullptr);
    ~Arinc429Widget();

    void setRawValue(const QString strValue);
    void setLabelValue(const QString strValue);
    void setSdiValue(const QString strValue);
    void setPayloadValue(const QString strValue);
    void setSsmValue(const QString strValue);
    void setParityValue(const QString strValue);
    QPushButton* getTextFieldForBit(const int i);
    unsigned int getBnrMsbPosition();
    unsigned int getBnrLsbPosition();
    double getBnrResolution();
    bool getBnrIsSigned();
    void setBnrResolutionValue(const double newValue);
    void setBnrRangeValue(const double newValue);
    double getBnrRangeValue();
    void displayBnrValue(const double value);
    QPushButton *getPushButtonForBit(const int bitNumber);

public slots:
    void parityValidity(const bool& isValid);

private slots:
    void inputValueChanged(const QString& newValue);
    void labelMsbFirstChanged(const int& state);
    void updateBnrDefinition();
    void internalParityTypeChanged(const int& state);

signals:
    void rawValueChanged(const QString&);
    void labelNumberMsbFirstChanged(const int&);
    void dwBitClicked(int bitNumber);
    void bnrMsbChanged(const int&);
    void bnrLsbChanged(const int&);
    void bnrRangeChanged(const double&);
    void bnrResolutionChanged(const double&);
    void bnrIsSignedChanged(const int&);
    void parityTypeChanged(const int&);

private:
    Ui::Arinc429Widget *ui;
};

#endif // ARINC429WIDGET_H
