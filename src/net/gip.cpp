#include <arpa/inet.h>
#include "base/gerr.h"
#include "gip.h"

// ----------------------------------------------------------------------------
// GIp
// ----------------------------------------------------------------------------
GIp& GIp::operator =(const char* rhs) {
  int res = inet_pton(AF_INET, rhs, &ip_);
  switch (res) {
    case 0:
      qWarning() << "inet_pton return zero ip=" << rhs;
      break;
    case 1: // succeed
      ip_ = ntohl(ip_);
      break;
    default:
      qWarning() << "inet_pton return " << res << " " << GLastErr();
  }
  return *this;
}

GIp::operator QString() const {
  quint32 ip = htonl(ip_);
  char s[INET_ADDRSTRLEN];
  const char* res = inet_ntop(AF_INET, &ip, s, INET_ADDRSTRLEN);
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

TEST(GIp, ctorTest) {
  GIp ip1; // ()

  GIp ip2{ip1}; // (const GIp&)

  GIp ip3{0x7F000001}; // (const quint32)

  GIp ip4{"127.0.0.1"}; // (const char*)

  GIp ip5{(QString)"127.0.0.2"}; // (const QString ip)
}

TEST(GIp, assignTest) {
  GIp ip1{"127.0.0.1"};
  GIp ip2;

  ip2 = ip1; // operator =(const GIp&)
  EXPECT_EQ(ip2, 0x7F000001);

  ip2 = 0x7F000001; // operator =(const quint32)
  EXPECT_EQ(ip2, 0x7F000001);

  ip2 = "127.0.0.1"; // operator =(const char*)
  EXPECT_EQ(ip2, 0x7F000001);

  ip2 = (QString)"127.0.0.1"; // operator =(const QString)
  EXPECT_EQ(ip2, 0x7F000001);
}

TEST(GIp, operatorTest) {
  GIp ip{"127.0.0.1"};

  quint32 ui; ui = ip; // operator quint32()
  EXPECT_EQ(ui, 0x7F000001);

  QString s1; s1 = (const char*)ip; //operator const char*()
  EXPECT_EQ(s1, "127.0.0.1");

  QString s2; s2 = (QString)ip; // operator QString()
  EXPECT_EQ(s2, "127.0.0.1");
}

TEST(GIp, funcTest) {
  GIp ip;

  ip = "127.0.0.1";
  EXPECT_TRUE(ip.isLocalHost());

  ip = "255.255.255.255";
  EXPECT_TRUE(ip.isBroadcast());

  ip = "224.0.0.0";
  EXPECT_TRUE(ip.isMulticast());
}

#endif // GTEST

