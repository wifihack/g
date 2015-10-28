#include "gjsonaux.h"
#include "gobj.h"

// ----------------------------------------------------------------------------
// QList<int>
// ----------------------------------------------------------------------------
QJsonValueRef operator << (QJsonValueRef ref, const QList<int>& intList) {
  QStringList strList;
  for(int i: intList) {
    QString s = QString::number(i);
    strList.append(s);
  }

  ref = strList.join(',');
  return ref;
}

QJsonValueRef operator >> (const QJsonValueRef ref, QList<int>& intList) {
  QString s = ref.toString();

  if (s != "") {
    QStringList strList = ref.toString().split(',');
    for(QString s: strList) {
      intList.append(s.toInt());
    }
  }

  return ref;
}

// ----------------------------------------------------------------------------
// GObj
// ----------------------------------------------------------------------------
QJsonValueRef operator << (QJsonValueRef ref, const GObj& obj) {
  QJsonObject json;

  ((GObj&)obj).save(json);

  ref = json;
  return ref;
}

QJsonValueRef operator >> (const QJsonValueRef ref, GObj& obj) {
  QJsonObject json = ref.toObject();

  if (!json.empty()) {
    obj.load(json);
  }

  return ref;
}

#ifdef QT_GUI_LIB

// ----------------------------------------------------------------------------
// QSplitter
// ----------------------------------------------------------------------------
QJsonValueRef operator << (QJsonValueRef ref, const QSplitter* splitter) {
  ref << splitter->sizes();
  return ref;
}

QJsonValueRef operator >> (const QJsonValueRef ref, QSplitter* splitter) {
  QList<int> sizes;
  ref >> sizes;
  if (sizes.count() != 0)
    splitter->setSizes(sizes);
  return ref;
}

// ----------------------------------------------------------------------------
// QWidget
// ----------------------------------------------------------------------------
#include <QPoint>
#include <QSize>
QJsonValueRef operator << (QJsonValueRef ref, const QWidget* widget) {
  QJsonObject json;

  QPoint pos = widget->pos();
  json["left"] = pos.x();
  json["top"] = pos.y();

  QSize size = widget->size();
  json["width"] = size.width();
  json["height"] = size.height();

  ref = json;
  return ref;
}

QJsonValueRef operator >> (QJsonValueRef ref, QWidget* widget) {
  QJsonObject json = ref.toObject();

  if (!json.isEmpty()) {
    QPoint pos;
    pos.setX(json["left"].toInt());
    pos.setY(json["top"].toInt());
    widget->move(pos);

    QSize size;
    size.setWidth(json["width"].toInt());
    size.setHeight(json["height"].toInt());
    widget->resize(size);
  }

  return ref;
}

#endif // QT_GUI_LIB
