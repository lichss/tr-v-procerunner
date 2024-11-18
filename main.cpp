#include <iostream>


#include "QtWidgetstr.h"
#include <QtWidgets/QApplication>

#include "NXInterface.h"
#include "x_jsonclass.h"

#if 1

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	QtWidgetstr w;
	w.ptrPath = "NULL";
	w.show();


	qInfo() << "run begin\n";
	
	//QString ptrPath = "D:\\env_tr\\u\\trptr\\tanhuangguan-shiyanmoxing.prt";

	/* 从json读取参数*/
	QString ptrPath = readJsonf(JSON_FilePath);

	w.updLabel(ptrPath);
	w.ptrPath = ptrPath;
	w.value1 = 1.11;

	return a.exec();
}
#else

int main() {
	qInfo() << "run begin\n";
	NXinterface nx;
	QString ptrPath = "D:\\env_tr\\u\\trptr\\tanhuangguan-shiyanmoxing.prt";
	//nx.SelectUgParams(ptrPath);
	QStringList qls = nx.GetExpression(ptrPath);
	for (auto item : qls)
		qInfo() << item;

	return 0;
}

#endif