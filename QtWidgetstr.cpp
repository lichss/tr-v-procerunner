#include "QtWidgetstr.h"

QtWidgetstr::QtWidgetstr(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    connect(ui.inputlineEdit, SIGNAL(returnPressed()), this, SLOT(uuslots1()));
    connect(ui.loadButton, &QPushButton::pressed, this, &QtWidgetstr::uuslots1);
    connect(ui.loadPtrButton, &QPushButton::pressed, this, &QtWidgetstr::loadPrtFileTotable);
    connect(ui.SaveButton, &QPushButton::pressed, this, &QtWidgetstr::saveTable);
    connect(ui.selectButton, &QPushButton::pressed, this, &QtWidgetstr::select);
    //saveTable

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

    this->ui.showlineEdit->setText(this->prtPath);
    this->ui.label->setText("1");

    return 0;
}

int QtWidgetstr::loadPrtFileTotable() {
    qInfo() << "Preses Button2\n";

    //this->ui.label->setText("loading ");
    qInfo() << "Loading..";
    //this->prtPath = "D:\\env_tr\\u\\trptr\\C_moog_qianzhiji.prt";
    this->pressionList = this->Nxi.GetExpression(this->prtPath);


    ui.tableWidget->setRowCount(this->pressionList.size());
    ui.tableWidget->setColumnCount(4);

 
    int row = 0;
    //delmtableMat();

    //QVector<QVector< QTableWidgetItem*>> qv_out;
    //mTableMat;
    for (auto item : pressionList) {
        QStringList strLsit = item.split('\t');
        QVector<QTableWidgetItem*> qv;

        QTableWidgetItem* name_ptr = new QTableWidgetItem(strLsit[0]);
        QTableWidgetItem* equation_ptr = new QTableWidgetItem(strLsit[1]);
        QTableWidgetItem* value_ptr = new QTableWidgetItem(strLsit[2]);
        QTableWidgetItem* unit_ptr = new QTableWidgetItem(strLsit[3]);


        if(name_ptr)
            ui.tableWidget->setItem(row, 0, name_ptr);
        if(equation_ptr)
            ui.tableWidget->setItem(row, 1, equation_ptr);
        if(value_ptr)
            ui.tableWidget->setItem(row, 2, value_ptr);
        if(unit_ptr)
            ui.tableWidget->setItem(row, 3, unit_ptr);
        row++;
    }
    

    
    updLabel(prtPath);
    

    return 0;
}

int QtWidgetstr::saveTable()
{
    qInfo() << "SaveButton pressed.";
    qInfo() << "Now ptr file" << prtPath;
    updLabel(prtPath);

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Prt Files (*.prt);;All Files (*)"));

    if (fileName.isEmpty()) {
        // 用户取消了保存操作
        return -1;
    }

    int row = ui.tableWidget->rowCount();
    int col = ui.tableWidget->columnCount();

    QStringList namevalue;
    for (int i = 0; i < row; i++) {       
        namevalue.append( ui.tableWidget->item(i, 0)->text() + "\t"
            + ui.tableWidget->item(i, 2)->text() );
    }
    Nxi.writeExpressions(prtPath,namevalue,fileName);


    return 0;
}

int QtWidgetstr::select() {
    qInfo() << "Select.\n";
    QSettings settings("TongYuan", "AmphibiousOptimize");
   // QString fileName = QFileDialog::getOpenFileName(this,"select prt", "", "PTR Files (*.prt);;All Files (*)");

    
//    QString UgsRouterPath = QFileDialog::getOpenFileName(this,"select ugs_routet", "", "EXE Files (*.exe);;All Files (*)");
    QString UgsRouterPath = sysenvirFind("UGS_ROUTER_PATH");
    if (UgsRouterPath.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "No EnvironmentVariable find.");
        QString UgsRouterPath = QFileDialog::getOpenFileName(this,"select ugs_routet", "", "EXE Files (*.exe);;All Files (*)");

    }
    Nxi.runUGwin(UgsRouterPath, this->prtPath);

    qInfo() << UgsRouterPath << "geted.\n";
    return 0;
}

int QtWidgetstr::updLabel(QString text) {

    ui.label->setText(text);
    return 0;
}

QString QtWidgetstr::sysenvirFind(QString envKey) {

    QString EnvValueString;
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    if (!env.contains(envKey)){
//        qInfo() << "妹找到啊，你根本就不在沈阳，你在哪呢？\n not find.w";
        return EnvValueString;
    }
    
 //   qInfo() << "有环境变量:\nfind env.as:\n" << env.value("UGS_ROUTER_PATH");
    return env.value(envKey);
    
}

