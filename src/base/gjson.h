// ----------------------------------------------------------------------------
//
// G Library
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#pragma once

#include <QDebug>
#include <QJsonObject>

// ----------------------------------------------------------------------------
// GJson
// ----------------------------------------------------------------------------
struct GJson {
  QJsonObject loadFromFile(QString fileName = "");
  void saveToFile(QJsonObject json, QString fileName = "");

  static GJson& instance();

protected:
  static QString defaultFileName();

  QString fileName_;
};
