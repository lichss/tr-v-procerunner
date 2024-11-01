#include "x_jsonclass.h"


QString readJsonf(QString jsonPath) {


	QString NjsonPath = QDir::fromNativeSeparators(jsonPath);
	qInfo() << "openning" << NjsonPath << "\n";

	QFile file(NjsonPath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Failed to open JSON file:" << NjsonPath;
		return "-1";
	}

	QByteArray jsonData = file.readAll();
	file.close();

	QJsonParseError jsonError;
	QJsonDocument doc = QJsonDocument::fromJson(jsonData, &jsonError);
	if (jsonError.error != QJsonParseError::NoError) {
		qDebug() << "Failed to parse JSON:" << jsonError.errorString();
		return "-1";
	}

	QJsonObject jsonObject = doc.object();

	// 处理 JSON 数据
	// 示例：获取 "name" 字段的值
	QString order = jsonObject["order1"].toString();
	//int order1 = jsonObject.value("order1").toInt();
	qInfo() << "get order:" << order;

	return order;
}


int xJson::readJson(QString jsonPath) {


	QString NjsonPath = QDir::fromNativeSeparators(jsonPath);
	qInfo() << "openning" << NjsonPath << "\n";

	QFile file(NjsonPath);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Failed to open JSON file:" << NjsonPath;
		return -1;
	}

	QByteArray jsonData = file.readAll();
	file.close();

	QJsonParseError jsonError;
	QJsonDocument doc = QJsonDocument::fromJson(jsonData, &jsonError);
	if (jsonError.error != QJsonParseError::NoError) {
		qDebug() << "Failed to parse JSON:" << jsonError.errorString();
		return -1;
	}

	QJsonObject jsonObject = doc.object();

	// 处理 JSON 数据
	// 示例：获取 "name" 字段的值
	QString name = jsonObject["city"].toString();
	int order1 = jsonObject.value("order1").toInt();
	qDebug() << "order1:" << order1;

	return 0;
}
