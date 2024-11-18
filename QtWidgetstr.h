#pragma once

#include <QtWidgets/QWidget>
#include <QProcess>
#include <QDebug>

/**/
#include "ui_QtWidgetstr.h"

/* user head file */
#include "NXInterface.h"


/* user Defines */

#define JSON_FilePath "orders.json"

class QtWidgetstr : public QWidget
{
    Q_OBJECT

public:
    
    NXinterface Nxi;

    QString prtPath;
    QVariant value1;
    QStringList pressionList;
    QVector<QVector<QTableWidgetItem*>> mTableMat;

    QtWidgetstr(QWidget *parent = nullptr);
    ~QtWidgetstr();

    int delmtableMat();
    int updLabel(QString text);

private slots:
    int uuslots1();
    int uuslots2();
    int saveTable();

    int select();


 
private:
    Ui::QtWidgetstrClass ui;
};
