#pragma once

#include <QWidget>

namespace Ui {
class A429BcdWidget;
}

class A429BcdWidget : public QWidget
{
    Q_OBJECT

public:
    explicit A429BcdWidget(QWidget *parent = nullptr);
    ~A429BcdWidget();

private:
    Ui::A429BcdWidget *ui;
};

