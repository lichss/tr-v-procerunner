#include "QtWidgetstr.h"

QtWidgetstr::QtWidgetstr(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    ui.lineEdit->setText("hihihi\n");
    //ui.setupUi(this);

}

QtWidgetstr::~QtWidgetstr()
{}
