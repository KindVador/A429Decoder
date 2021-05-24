#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setGeometry(w.geometry().x(), w.geometry().y(), 0, 0);
    w.show();
    return a.exec();
}
