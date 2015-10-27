#ifdef QT_GUI_LIB

#include <QGridLayout>
#include "gpropitemobjectname.h"
#include "gpropwidget.h"

// ----------------------------------------------------------------------------
// GPropWidget
// ----------------------------------------------------------------------------
GPropWidget::GPropWidget(QWidget *parent) : QTreeWidget(parent) {
  this->setColumnCount(2);
  this->setHeaderLabels(QStringList() << "property" << "value");
  QLayout* layout = new QGridLayout(this);
  layout->setMargin(0);
  obj_ = nullptr;
}

GPropWidget::~GPropWidget() {
}

QObject* GPropWidget::object() {
  return obj_;
}

void GPropWidget::setObject(GObj* obj) {
  if (obj == obj_) return;
  clear();
  obj_ = obj;

  QMetaProperty mpro = obj->metaObject()->property(0); // objectName
  GPropItemObjectName* root = new GPropItemObjectName(this, obj, mpro);
  root->update();
  QTreeWidgetItem* item = root->item_;
  obj_->createPropItems(item);

  expandAll();
}

#endif // QT_GUI_LIB
