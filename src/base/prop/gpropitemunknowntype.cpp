#include "gpropitemunknowntype.h"

#ifdef QT_GUI_LIB

// ----------------------------------------------------------------------------
// GPropItemUnknownType
// ----------------------------------------------------------------------------
GPropItemUnknownType::GPropItemUnknownType(QTreeWidgetItem* parent, QObject* object, QMetaProperty mpro) : GPropItem(parent, object, mpro) {
  item_->setBackground(1, QBrush(Qt::lightGray));
}

#endif // QT_GUI_LIB
