#pragma once

#include <QtWidgets/QWidget>
#include <QProcess>
#include <QDebug>

/**/
#include "ui_QtWidgetstr.h"

/* user head file */
#include "NXInterface.h"

class QtWidgetstr : public QWidget
{
    Q_OBJECT

public:
    
    NXinterface Nxi;

    QString ptrPath;
    QVariant value1;
    QStringList pressionList;
    QVector<QVector<QTableWidgetItem*>> mTableMat;

    QtWidgetstr(QWidget *parent = nullptr);
    ~QtWidgetstr();

    int delmtableMat();
private slots:
    int uuslots1();
    int uuslots2();
    int saveTable();

 
private:
    Ui::QtWidgetstrClass ui;
};
