#ifndef __NXINTERFACE_H__
#define __NXINTERFACE_H__



#include <uf_defs.h>
#include <NXOpen/NXException.hxx>
#include <NXOpen/Session.hxx>
#include <NXOpen/BasePart.hxx>
#include <NXOpen/Expression.hxx>
#include <NXOpen/ExpressionCollection.hxx>
#include <NXOpen/NXObject.hxx>
#include <NXOpen/Part.hxx>
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/PartLoadStatus.hxx>
#include <NXOpen/PartSaveStatus.hxx>
#include <NXOpen/Preferences_SessionModeling.hxx>
#include <NXOpen/Preferences_SessionPreferences.hxx>
#include <NXOpen/Unit.hxx>
#include <NXOpen/UnitCollection.hxx>
#include <NXOpen/Update.hxx>
#include <NXOpen/NXString.hxx>
#include <iostream>
//#include <QApplication>
#include <QtWidgets/QApplication>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

//#include "../618/core/hy_context.h"
#include "dummy_paramset.h"	/* 增加这个.h是为了让测试通过。正常使用应该用上面的 ../618/core/hy_context.h  而不是这个 */

#define NX_EXPORT_D _declspec(dllexport)



class NX_EXPORT_D NXinterface
{
public:

	int nx_test();	/* 不常用 */
	int UgRun(const ParamSet& param_set, int times, QString save_file_name, QString& error_message);
	
	QStringList GetExpression(QString file_name); /*获取 全部表达式 不加过滤*/
	
	int GetUgUnitType(const ParamSet& param_set, QString& error_message);
	
	QStringList SelectUgParams(const QString& file_name);

	QStringList SelectUgParams(const QString& file_name, const QString& filter_RegularExpression);


private:

};


#endif // !__NXINTERFACE_H__