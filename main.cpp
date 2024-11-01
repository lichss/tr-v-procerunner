#include "QtWidgetstr.h"
#include <QtWidgets/QApplication>
#include "NXInterface.h"
#include <iostream>

#if 0
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWidgetstr w;

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