#include "gjsonaux.h"
#include "gobj.h"

// ----------------------------------------------------------------------------
// operator
// ----------------------------------------------------------------------------
QJsonValueRef& operator << (QJsonValueRef&& ref, const QList<int>& intList) {
  QStringList strList;
  for(int i: intList) {
    QString s = QString::number(i);
    strList.append(s);
  }
  ref = strList.join(',');
  return ref;
}

QJsonValueRef& operator >> (const QJsonValueRef&& ref, QList<int>& intList) {
  QString s = ref.toString();
  if (s != "") {
    QStringList strList = ref.toString().split(',');
    for(QString s: strList) {
      intList.append(s.toInt());
    }
  }
  return (QJsonValueRef&)ref;
}

QJsonValueRef& operator << (QJsonValueRef&& ref, const GObj& obj) {
  QJsonObject json;
  json << obj;
  ref = json;
  return ref;
}

QJsonValueRef& operator >> (const QJsonValueRef&& ref, GObj& obj) {
  QJsonObject json = ref.toObject();
  json >> obj;
  return (QJsonValueRef&)ref;
}

QJsonObject& operator << (QJsonObject& json, const GObj& obj) {
  ((GObj&)obj).save(json);
  return json;
}

QJsonObject& operator >> (const QJsonObject& json, GObj& obj) {
  if (!json.empty())
    obj.load(json);
  return (QJsonObject&)json;
}

#ifdef QT_GUI_LIB

#include <QPoint>
#include <QSize>

QJsonValueRef& operator << (QJsonValueRef&& ref, const QWidget& widget) {
  QJsonObject json;
  json << widget;
  ref = json;
  return ref;
}

QJsonValueRef& operator >> (const QJsonValueRef&& ref, QWidget& widget) {
  QJsonObject json = ref.toObject();
  json >> widget;
  return (QJsonValueRef&)ref;
}

QJsonObject& operator << (QJsonObject& json, const QWidget& widget) {
  QPoint pos = widget.pos();
  json["left"] = pos.x();
  json["top"] = pos.y();

  QSize size = widget.size();
  json["width"] = size.width();
  json["height"] = size.height();

  return json;
}

QJsonObject& operator >> (const QJsonObject& json, QWidget& widget) {
  if (json.isEmpty()) return (QJsonObject&)json;

  QPoint pos;
  pos.setX(json["left"].toInt());
  pos.setY(json["top"].toInt());
  widget.move(pos);

  QSize size;
  size.setWidth(json["width"].toInt());
  size.setHeight(json["height"].toInt());
  widget.resize(size);

  return (QJsonObject&)json;
}

#endif // QT_GUI_LIB
