#include "gjsonaux.h"

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
  QStringList strList = ref.toString().split(',');
  for(QString s: strList) {
    intList.append(s.toInt());
  }
  return (QJsonValueRef&)ref;
}

#ifdef QT_GUI_LIB

#include <QPoint>
#include <QSize>

QJsonObject& operator << (QJsonObject& json, QWidget& widget) {
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
