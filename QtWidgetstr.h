#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtWidgetstr.h"

class QtWidgetstr : public QWidget
{
    Q_OBJECT

public:
    QtWidgetstr(QWidget *parent = nullptr);
    ~QtWidgetstr();

 
private:
    Ui::QtWidgetstrClass ui;
};
