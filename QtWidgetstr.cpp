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

}

QtWidgetstr::~QtWidgetstr()
{}

int QtWidgetstr::uuslots1() {
    qInfo() << "Preses\n";
    this->ui.lineEdit->setText("aaa");
    this->ui.showlineEdit->setText(this->ptrPth);

    this->ui.label->setText("aaa");
    //ui.lineEdit->setText("hihihi\n");
    //this->ui.lineEdit->text() = "aaa";
    return 0;
}
