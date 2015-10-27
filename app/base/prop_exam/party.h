#pragma once

#include "person.h"

struct Party : public GObj {
  Q_OBJECT
  Q_PROPERTY(QObject* owner READ getOwner)
  Q_PROPERTY(QString partyName MEMBER partyName_)
  Q_PROPERTY(QString address MEMBER address_)
  Q_PROPERTY(bool free MEMBER free_)

  Person* getOwner() { return &owner_; }

public:
  Person owner_;
  QString partyName_;
  QString address_;
  bool free_{false};
};
