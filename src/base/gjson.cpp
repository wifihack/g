#include <QCoreApplication>
#include <QDir>
#include <QJsonDocument>
#include "gjson.h"

// ----------------------------------------------------------------------------
// GJson
// ----------------------------------------------------------------------------
QJsonObject GJson::loadFromFile(QString fileName) {
  if (fileName == "")
    fileName = fileName_;
  if (fileName == "")
    fileName = defaultFileName();
  fileName_ = fileName;

  if (!QFile::exists(fileName)) {
    return QJsonObject();
  }
  QFile file(fileName);
  if (!file.open(QFile::ReadOnly)) {
    qWarning() << QString("file open(%1) failed(%2)").arg(fileName, file.errorString());
    return QJsonObject();
  }
  QByteArray ba = file.readAll();
  QJsonDocument doc = QJsonDocument::fromJson(ba);

  return doc.object();
}

void GJson::saveToFile(QJsonObject json, QString fileName) {
  if (fileName == "")
    fileName = fileName_;
  if (fileName == "")
    fileName = defaultFileName();
  fileName_ = fileName;

  QFile file(fileName);
  if (!file.open(QFile::WriteOnly)) {
    qWarning() << QString("file open(%1) failed(%2)").arg(fileName, file.errorString());
    return;
  }
  QJsonDocument doc;
  doc.setObject(json);
  file.write(doc.toJson());
}

GJson& GJson::instance() {
  static GJson json;
  return json;
}

QString GJson::defaultFileName() {
  QString res;
  res = QCoreApplication::applicationFilePath();
  res += ".json";
  return res;
}

