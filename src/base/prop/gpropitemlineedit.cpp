#include "gpropitemlineedit.h"

#ifdef QT_GUI_LIB

// ----------------------------------------------------------------------------
// GPropItemLineEdit
// ----------------------------------------------------------------------------
GPropItemLineEdit::GPropItemLineEdit(QTreeWidget* widget, QObject* object, QMetaProperty mpro) : GPropItem(widget, object, mpro) {
  lineEdit_ = new QLineEdit(widget);
  lineEdit_->setFrame(false);
  widget->setItemWidget(item_, 1, lineEdit_);
}

GPropItemLineEdit::GPropItemLineEdit(QTreeWidgetItem* parent, QObject* object, QMetaProperty mpro) : GPropItem(parent, object, mpro) {
  QTreeWidget* treeWidget = item_->treeWidget();
  Q_ASSERT(treeWidget != nullptr);
  lineEdit_ = new QLineEdit(treeWidget);
  lineEdit_->setFrame(false);
  treeWidget->setItemWidget(item_, 1, lineEdit_);
}

#endif // QT_GUI_LIB
