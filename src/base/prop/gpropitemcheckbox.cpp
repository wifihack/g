#include "gpropitemcheckbox.h"

#ifdef QT_GUI_LIB

// ----------------------------------------------------------------------------
// GPropItemCheckBox
// ----------------------------------------------------------------------------
GPropItemCheckBox::GPropItemCheckBox(QTreeWidgetItem* parent, QObject* object, QMetaProperty mpro) : GPropItem(parent, object, mpro) {
  QTreeWidget* treeWidget = item_->treeWidget();
  Q_ASSERT(treeWidget != nullptr);
  checkBox_ = new QCheckBox(treeWidget);
  treeWidget->setItemWidget(item_, 1, checkBox_);
}

#endif // QT_GUI_LIB
