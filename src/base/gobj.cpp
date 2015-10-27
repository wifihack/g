#include "gobj.h"

GObj::~GObj() {
  if (err != nullptr) {
    delete err;
    err = nullptr;
  }
}

bool GObj::open() {
  SET_ERR(GStdErr(g::VIRTUAL_FUNCTION_CALL, "virtual function call"));
  return false;
}

bool GObj::close() {
  SET_ERR(GStdErr(g::VIRTUAL_FUNCTION_CALL, "virtual function call"));
  return false;
}

void GObj::load(const QJsonObject json) {
  const QMetaObject* mobj = metaObject();
  int count = mobj->propertyCount();
  for (int i = 0; i < count; i++) {
    QMetaProperty mpro = mobj->property(i);
    load(json, mpro);
  }
}

void GObj::save(QJsonObject& json) {
  const QMetaObject* mobj = metaObject();
  int count = mobj->propertyCount();
  for (int i = 0; i < count; i++) {
    QMetaProperty mpro = mobj->property(i);
    save(json, mpro);
  }
}

bool GObj::load(const QJsonObject json, QMetaProperty mpro) {
  const char* propName = mpro.name();
  int userType = mpro.userType();
  QVariant variant = json[propName];
  bool res = false;

  if (mpro.isEnumType()) {
    QMetaEnum menum = mpro.enumerator();
    QString key = variant.toString();
    if (key == "") return true;
    int value = menum.keyToValue(qPrintable(key));
    res = setProperty(propName, value);
  } else
  switch (userType) {
    case QMetaType::Bool:
      res = setProperty(propName, variant.toBool());
      break;

    case QMetaType::QChar:
      res = setProperty(propName, variant.toString());
      break;

    case QMetaType::QObjectStar: {
        GObj* obj = qvariant_cast<GObj*>(property(propName));
        Q_ASSERT(obj != nullptr);
        obj->load(json[propName].toObject());
        return true;
      }

    case QMetaType::Char:
    case QMetaType::Double:
    case QMetaType::Float:
    case QMetaType::Int:
    case QMetaType::LongLong:
    case QMetaType::Short:
    case QMetaType::UChar:
    case QMetaType::UInt:
    case QMetaType::ULongLong:
    case QMetaType::UShort: {
        QString s = variant.toString();
        if (s == "") return true;
        res = setProperty(propName, QVariant::fromValue<QString>(s));
        break;
      }

    case QMetaType::QString: {
        QString s = variant.toString();
        res = setProperty(propName, QVariant::fromValue<QString>(s));
        break;
      }
  }

  if (!res) {
    qWarning() << QString("%1::load(%2, %3) return false").arg(metaObject()->className(), propName, variant.toString());
  }
  return res;
}

bool GObj::save(QJsonObject& json, QMetaProperty mpro) {
  const char* propName = mpro.name();
  int userType = mpro.userType();
  QVariant variant = property(propName);

  if (mpro.isEnumType()) {
    QMetaEnum menum = mpro.enumerator();
    int value = variant.toInt();
    QString key = menum.valueToKey(value);
    json[propName] = key;
    return true;
  }

  switch (userType) {
    case QMetaType::Bool:
      json[propName] = variant.toBool();
      return true;

    case QMetaType::QChar:
      json[propName] = property(propName).toString();
      return true;

    case QMetaType::QObjectStar: {
        GObj* obj = qvariant_cast<GObj*>(variant);
        Q_ASSERT(obj != nullptr);
        QJsonObject childJson;
        obj->save(childJson);
        json[propName] = childJson;
        return true;
      }

    case QMetaType::Char:
    case QMetaType::Double:
    case QMetaType::Float:
    case QMetaType::Int:
    case QMetaType::LongLong:
    case QMetaType::Short:
    case QMetaType::UChar:
    case QMetaType::UInt:
    case QMetaType::ULongLong:
    case QMetaType::UShort: {
        QString s = variant.toString();
        json[propName] = s;
        return true;
      }

    case QMetaType::QString: {
         QString s = variant.toString();
         json[propName] = s;
         return true;
       }
  }

  qWarning() << QString("%1::save(%2, %3) return false").arg(metaObject()->className(), propName, variant.toString());
  return false;
}

#ifdef QT_GUI_LIB

#include "base/prop/gpropitembool.h"
#include "base/prop/gpropitemenum.h"
#include "base/prop/gpropitemobjectname.h"
#include "base/prop/gpropitemqchar.h"
#include "base/prop/gpropitemqobjectstar.h"
#include "base/prop/gpropitemqvariant.h"
#include "base/prop/gpropitemunknowntype.h"

void GObj::createPropItems(QTreeWidgetItem* parent) {
  const QMetaObject* mobj = metaObject();
  int propCount = mobj->propertyCount();
  for (int i = 1; i < propCount; i++) { // skip objectName
    QMetaProperty mpro = mobj->property(i);
    GPropItem* item = createPropItem(parent, this, mpro);
    if (item == nullptr) {
      qWarning() << "item is nullptr typeName='" << mpro.typeName() <<"' name='"<< mpro.name() << "'";
      item = new GPropItemUnknownType(parent, this, mpro);
    }
    item->update();
  }
}

GPropItem* GObj::createPropItem(QTreeWidgetItem* parent, QObject* object, QMetaProperty mpro) {
  const char* propName = mpro.name();
  int userType = mpro.userType();

  if (mpro.isEnumType()) {
    return new GPropItemEnum(parent, object, mpro);
  }

  if ((QString)propName == "objectName") {
    return new GPropItemObjectName(parent, object, mpro);
  }

  switch (userType) {
    case QMetaType::Bool:
      return new GPropItemBool(parent, object, mpro);

    case QMetaType::QChar:
      return new GPropItemQChar(parent, object, mpro);

    case QMetaType::QObjectStar:
      return new GPropItemQObjectStar(parent, object, mpro);

    case QMetaType::Char:
    case QMetaType::Double:
    case QMetaType::Float:
    case QMetaType::Int:
    case QMetaType::LongLong:
    case QMetaType::QString:
    case QMetaType::Short:
    case QMetaType::UChar:
    case QMetaType::UInt:
    case QMetaType::ULongLong:
    case QMetaType::UShort:
      return new GPropItemQVariant(parent, object, mpro);
  }

  qWarning() << QString("can not create GPropItem(object=%1 propName=%2)").arg(object->metaObject()->className(), propName);
  return nullptr;
}

#endif // QT_GUI_LIB
