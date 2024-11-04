#include "QtWidgetstr.h"
#include "qpushbutton.h"


QtWidgetstr::QtWidgetstr(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    //ui.lineEdit->setText("hihihi\n");
    //ui.setupUi(this);
    
    //connect(ui.lineEdit,SIGNAL(returnpres);
    
    connect(ui.lineEdit, SIGNAL(returnPressed()), this, SLOT(uuslots1()));
    connect(ui.loadButton, &QPushButton::pressed, this, &QtWidgetstr::uuslots1);
    connect(ui.cancelButton, &QPushButton::pressed, this, &QtWidgetstr::uuslots2);

}

QtWidgetstr::~QtWidgetstr()
{}

int QtWidgetstr::uuslots1() {
    qInfo() << "Preses Button1\n";
    this->ui.lineEdit->setText("1");
    this->ui.showlineEdit->setText(this->ptrPath);

    this->ui.label->setText("1");
    //ui.lineEdit->setText("hihihi\n");
    //this->ui.lineEdit->text() = "aaa";
    return 0;
}

int QtWidgetstr::uuslots2() {
    qInfo() << "Preses Button2\n";

    this->ui.label->setText("loading ");

    this->ui.lineEdit->setText("2");
    this->ptrPath = "D:\\env_tr\\u\\trptr\\tanhuangguan-shiyanmoxing.prt";
    this->pression_list = this->Nxi.GetExpression(this->ptrPath);

    this->ui.showlineEdit->setText(this->pression_list[0].toUpper());
    this->ui.label->setText("over ");

    

    return 0;
}
