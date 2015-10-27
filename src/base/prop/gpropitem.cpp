#include "gpropitem.h"

#ifdef QT_GUI_LIB

// ----------------------------------------------------------------------------
// GPropItem
// ----------------------------------------------------------------------------
GPropItem::GPropItem(QTreeWidget* widget, QObject* object, QMetaProperty mpro) {
  item_ = new QTreeWidgetItem(widget);
  object_ = object;
  mpro_ = mpro;
  item_->setText(0, mpro_.name());
}

GPropItem::GPropItem(QTreeWidgetItem* parent, QObject* object, QMetaProperty mpro) {
  item_ = new QTreeWidgetItem(parent);
  object_ = object;
  mpro_ = mpro;
  item_->setText(0, mpro_.name());
}


#endif // QT_GUI_LIB
