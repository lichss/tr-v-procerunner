#include <iostream>


#include "QtWidgetstr.h"
#include <QtWidgets/QApplication>

#include "NXInterface.h"
#include "x_jsonclass.h"

#if 1
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWidgetstr w;
    w.ptrPth = "NULL";


    qInfo() << "run begin\n";
    NXinterface nx;
    //QString ptrPath = "D:\\env_tr\\u\\trptr\\tanhuangguan-shiyanmoxing.prt";

    QString ptrPath =  readJsonf("orders.json");
    w.ptrPth = ptrPath;
     w.show();

    return a.exec();
}
#else

int main() {
    qInfo() << "run begin\n";
    NXinterface nx;
    QString ptrPath = "D:\\env_tr\\u\\trptr\\tanhuangguan-shiyanmoxing.prt";
    //nx.SelectUgParams(ptrPath);
    QStringList qls =  nx.GetExpression(ptrPath);
    for (auto item : qls)
        qInfo() << item;

    return 0;
}

#endif