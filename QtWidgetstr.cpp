#include "QtWidgetstr.h"
#include "qpushbutton.h"


#include <qvector.h>
#include <qlist.h>
QtWidgetstr::QtWidgetstr(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    connect(ui.inputlineEdit, SIGNAL(returnPressed()), this, SLOT(uuslots1()));
    connect(ui.loadButton, &QPushButton::pressed, this, &QtWidgetstr::uuslots1);
    connect(ui.loadPtrButton, &QPushButton::pressed, this, &QtWidgetstr::uuslots2);

}

QtWidgetstr::~QtWidgetstr()
{}

int QtWidgetstr::delmtableMat()
{
    
    try{
        // QVector<QVector<QTableWidgetItem*>> mTableMat;
        for (auto row : mTableMat) {
            for (auto col : row) {
                delete col;
            }
            row.clear();
        }
        mTableMat.clear();
        return 0;
    }
    catch (const std::exception& e) {
        qDebug() << "Exception caught in delmtableMat: " << e.what();
        return -1;
    }
}

int QtWidgetstr::uuslots1() {
    qInfo() << "Preses Button1\n";
    qInfo() << "inputline edit:" << ui.inputlineEdit->text();

    this->ui.showlineEdit->setText(this->ptrPath);
    this->ui.label->setText("1");

    return 0;
}

int QtWidgetstr::uuslots2() {
    qInfo() << "Preses Button2\n";

    this->ui.label->setText("loading ");
    this->ptrPath = "D:\\env_tr\\u\\trptr\\C_moog_qianzhiji.prt";
    this->pressionList = this->Nxi.GetExpression(this->ptrPath);


    ui.tableWidget->setRowCount(this->pressionList.size());
 
    int row = 0;
    delmtableMat();

    //QVector<QVector< QTableWidgetItem*>> qv_out;
    //mTableMat;
    for (auto item : pressionList) {
        QStringList strLsit = item.split('\t');
        QVector<QTableWidgetItem*> qv;

        QTableWidgetItem* name_ptr = new QTableWidgetItem(strLsit[0]);
        QTableWidgetItem* equation_ptr = new QTableWidgetItem(strLsit[1]);
        QTableWidgetItem* unit_ptr = new QTableWidgetItem(strLsit[2]);

        qv.append(name_ptr);
        qv.append(equation_ptr);
        qv.append(unit_ptr);
        mTableMat.append(qv);

        if(name_ptr)
            ui.tableWidget->setItem(row, 0, name_ptr);
        if(equation_ptr)
            ui.tableWidget->setItem(row, 1, equation_ptr);
        if(unit_ptr)
            ui.tableWidget->setItem(row, 2, unit_ptr);
        row++;
        //qInfo() << "-------------------------------";
        //if (row > 4)
        //    break;
    }
    QTableWidgetItem* test = mTableMat[2][2];
    if (test)
        qInfo() << "watch!! : " << (*test).text();
    else
        qInfo() << "nullptr";


    
    this->ui.label->setText("over ");

    return 0;
}




