#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <a429word.hpp>
#include <arinc429widget.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updateView();
    void updateBnrValue();
    void showAboutWindow();
    void showDwBlock(const bool& state);
    void showBnrBlock(const bool& state);
    void showBcdBlock(const bool& state);

private slots:
    void valueChangedAction(const QString& newValue);
    void labelMsbFirstCheckBoxChanged(const int& state);
    void toggleDwBit(const int& bitNumber);
    void updateDwBlock();
    void updateMsbLsbLimits();
    void updateBnrRangeValue(const double& resolution);
    void updateBnrResolutionValue(const double& bnrRange);
    void updateBnrIsSignedValue(const int& state);
    void parityTypeChanged(const int& state);

private:
    Ui::MainWindow *ui;
    A429Word *a429Word;
};
#endif // MAINWINDOW_H
