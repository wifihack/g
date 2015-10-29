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

#include <netinet/in.h>
#include <QString>

// ----------------------------------------------------------------------------
// GIp6
// ----------------------------------------------------------------------------
struct GIp6 final {
  const static int SIZE = 16;
  typedef quint8 Addr[SIZE];

  GIp6() {}
  GIp6(const GIp6& rhs) { memcpy(ip6_, rhs.ip6_, SIZE); }
  GIp6(const Addr& rhs) { memcpy(ip6_, rhs, SIZE); }
  GIp6(const char* rhs) { operator =(rhs); }
  GIp6(const QString rhs) { operator =(rhs); }
  GIp6(const struct in6_addr& rhs) { operator=(rhs); }

  GIp6& operator =(const GIp6& rhs) { memcpy(ip6_, rhs.ip6_, SIZE); return *this; }
  GIp6& operator =(const Addr& rhs) { memcpy(ip6_, rhs, SIZE); return *this; }
  GIp6& operator =(const char* rhs);
  GIp6& operator =(const QString& rhs) { *this = qPrintable(rhs); return *this; }
  GIp6& operator =(const struct in6_addr& rhs) { memcpy(ip6_, &rhs, SIZE); return *this; }

  bool operator ==(const GIp6& rhs) const { return memcmp(ip6_, rhs.ip6_, SIZE) == 0; }

  explicit operator const quint8*() const { return ip6_; }
  explicit operator const char*() const { return qPrintable((QString)*this); }
  explicit operator QString() const;

  void clear() { memset(ip6_, 0, SIZE); }

public:
  bool isLocalHost() {
    return false; // gilgil temp 2015.06.19
  }

  bool isBroadcast() {
    return false; // gilgil temp 2015.06.19
  }

  bool isMulticast() {
    return false; // gilgil temp 2015.06.19
  }

protected:
  Addr ip6_;
};
