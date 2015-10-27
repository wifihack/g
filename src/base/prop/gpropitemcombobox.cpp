#include "gpropitemcombobox.h"

#ifdef QT_GUI_LIB

// ----------------------------------------------------------------------------
// GPropItemEnum
// ----------------------------------------------------------------------------
GPropItemComboBox::GPropItemComboBox(QTreeWidgetItem* parent, QObject* object, QMetaProperty mpro) : GPropItem(parent, object, mpro) {
  QTreeWidget* treeWidget = dynamic_cast<QTreeWidget*>(item_->treeWidget());
  Q_ASSERT(treeWidget != nullptr);
  comboBox_ = new QComboBox(treeWidget);
  treeWidget->setItemWidget(item_, 1, comboBox_);
}

#endif // QT_GUI_LIB
