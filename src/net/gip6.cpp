#include <arpa/inet.h>
#include "base/gerr.h"
#include "gip6.h"

// ----------------------------------------------------------------------------
// GIp6
// ----------------------------------------------------------------------------
GIp6& GIp6::operator =(const char* rhs) {
  int res = inet_pton(AF_INET6, rhs, &ip6_);
  switch (res) {
    case 0:
      qWarning() << "inet_pton return zero ip=" << rhs;
      break;
    case 1: // succeed
      break;
    default:
      qWarning() << "inet_pton return " << res << " " << GLastErr();
  }
  return *this;
}

GIp6::operator QString() const {
  char s[INET6_ADDRSTRLEN];
  const char* res = inet_ntop(AF_INET6, &ip6_, s, INET6_ADDRSTRLEN);
  if (res == nullptr) {
    qWarning() << "inet_ntop return null " << GLastErr();
    return QString();
  }
  return QString{s};
}

// ----------------------------------------------------------------------------
// GTEST
// ----------------------------------------------------------------------------
#ifdef GTEST
#include <gtest/gtest.h>

static GIp6::Addr _loopback{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};

TEST(GIp6, ctorTest) {
  GIp6 ip61; // ()

  GIp6 ip62{ip61}; // (const GIp& rhs)

  GIp6 ip63{_loopback}; // (const Addr&)

  GIp6 ip64{"::1"}; // (const char*)

  GIp6 ip65{(QString)"::2"}; // (const QString)
}

TEST(GIp6, assignTest) {
  GIp6 ip61{"::1"};
  GIp6 ip62;

  ip62 = ip61; // operator =(const GIp6&)
  EXPECT_EQ(ip62, ip61);

  ip62 = _loopback; // operator =(const Addr&)
  EXPECT_EQ(ip62, _loopback);

  ip62 = (QString)"::1"; // operator =(const char*)
  EXPECT_EQ(ip62, _loopback);

  ip62 = (QString)"::1"; // operator =(const QString&)
  EXPECT_EQ(ip62, _loopback);
}

TEST(GIp6, operatorTest) {
  GIp6 ip6{"::1"};

  const quint8* ui = (const quint8*)ip6; // operator const quint8*()
  GIp6::Addr temp;
  for (int i = 0; i < GIp6::SIZE; i++)
    temp[i] = *ui++;
  EXPECT_EQ(ip6, temp);

  QString s1 = (const char*)ip6; // operator const char*()
  EXPECT_EQ(s1, "::1");

  QString s2 = (QString)ip6; // operator QString()
  EXPECT_EQ(s2, "::1");
}

/*
TEST(GIp, funcTest) {
  GIp6 ip6;

  ip = "127.0.0.1";
  EXPECT_TRUE(ip.isLocalHost());

  ip = "255.255.255.255";
  EXPECT_TRUE(ip.isBroadcast());

  ip = "224.0.0.0";
  EXPECT_TRUE(ip.isMulticast());
}
*/
// ----------------------------------

#endif // GTEST
