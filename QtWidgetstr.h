#pragma once

#include <QtWidgets/QWidget>
#include <QProcess>
#include <QDebug>


#include "ui_QtWidgetstr.h"

class QtWidgetstr : public QWidget
{
    Q_OBJECT

public:
    QString ptrPth;
    QtWidgetstr(QWidget *parent = nullptr);
    ~QtWidgetstr();

private slots:
    int uuslots1();
 
private:
    Ui::QtWidgetstrClass ui;
};
