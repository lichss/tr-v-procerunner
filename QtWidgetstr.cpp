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

#if 1

    int row = 0;
    for (auto item : pressionList) {
        QStringList strLsit = item.split('\t');
        
        ui.tableWidget->setItem(row, 0, new QTableWidgetItem(strLsit[0]));
        ui.tableWidget->setItem(row, 1, new QTableWidgetItem(strLsit[1]));
        ui.tableWidget->setItem(row, 2, new QTableWidgetItem(strLsit[2]));
        row++;
    }

#else
    QVector <QVector< QTableWidgetItem >> qtw;
    QList<QStringList> qLsLs;
    auto itr = qtw.begin();
    for (auto item : pressionList)
    {
        int i = 0;
        qLsLs[i] = item.split('\t');
        qtw.append(QVector<QTableWidgetItem> {QTableWidgetItem(qLsLs[i][0]), QTableWidgetItem(qLsLs[i][1]), QTableWidgetItem(qLsLs[i][2])})
        
        *qls = item.split('\t');
        qInfo() << (*qls)[0];
        //qtw.append(*qls);  /*¼ÇµÃÉ¾³ý qtw*/
    }
    return 0; //debug


#endif
    
    this->ui.label->setText("over ");

    return 0;
}




