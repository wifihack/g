#pragma once

#include <GObj>

class Person : public GObj {
  Q_OBJECT
  Q_PROPERTY(QString name MEMBER name_)
  Q_PROPERTY(int age MEMBER age_)
  Q_PROPERTY(Qt::CheckState checkState MEMBER checkState_)
  Q_PROPERTY(Sex sex MEMBER sex_)
  Q_ENUMS(Sex)

public:
  enum Sex {
    Unknown = 100,
    Male = 200,
    Female = 300
  };

public:
  QString name_;
  int age_{0};
  Qt::CheckState checkState_{Qt::PartiallyChecked};
  Sex sex_{Male};
};
