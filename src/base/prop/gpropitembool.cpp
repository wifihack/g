#include "gpropitembool.h"

#ifdef QT_GUI_LIB

// ----------------------------------------------------------------------------
// GPropItemBool
// ----------------------------------------------------------------------------
GPropItemBool::GPropItemBool(QTreeWidgetItem* parent, QObject* object, QMetaProperty mpro) : GPropItemCheckBox(parent, object, mpro) {
  QObject::connect(checkBox_, SIGNAL(clicked(bool)), this, SLOT(myClicked(bool)));
}

void GPropItemBool::update() {
  QVariant value = object_->property(mpro_.name());
  checkBox_->setChecked(value.toBool());
}

void GPropItemBool::myClicked(bool checked) {
  bool res = object_->setProperty(mpro_.name(), checked);
  if (!res) {
    qWarning() << QString("object->setProperty(%1, %d) return false").arg(mpro_.name()).arg(checked);
  }
  update();
}

#endif // QT_GUI_LIB
