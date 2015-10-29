#include "gmac.h"

// ----------------------------------------------------------------------------
// GMac
// ----------------------------------------------------------------------------
GMac::GMac(const QString s) {
  int i;
  uint8_t* p;
  uint8_t ch1, ch2;

  QByteArray arr = s.toLatin1();
  p = (uint8_t*)arr.constData();
  for (i = 0 ; i < SIZE; i++)
  {
    ch1 = *p++;
    if (ch1 >= 'a')
      ch1 = ch1 - 'a' + 10;
    else
    if (ch1 >= 'A')
      ch1 = ch1 - 'A' + 10;
    else
      ch1 = ch1 - '0';
    ch2 = *p++;
    if (ch2 >= 'a')
      ch2 = ch2 - 'a' + 10;
    else if (ch2 >= 'A')
      ch2 = ch2 - 'A' + 10;
    else
      ch2 = ch2 - '0';
    value[i] = (ch1 << 4) + ch2;
    while (*p == '-' || *p == ':') p++;
  }
}

QString GMac::str() const {
  uint8_t ch1, ch2;
  int i, index;
  char buf[SIZE * 3]; // enough size

  index = 0;
  for (i = 0; i < SIZE; i++)
  {
    ch1 = value[i] & 0xF0;
    ch1 = ch1 >> 4;
    if (ch1 > 9)
      ch1 = ch1 + 'A' - 10;
    else
      ch1 = ch1 + '0';
    ch2 = value[i] & 0x0F;
    if (ch2 > 9)
      ch2 = ch2 + 'A' - 10;
    else
      ch2 = ch2 + '0';
    buf[index++] = ch1;
    buf[index++] = ch2;
    if (i == 2)
      buf[index++] = '-';
  }
  buf[index] = '\0';
  return (QString(buf));
}

GMac GMac::randomMac() {
  GMac res;
  for (int i = 0; i < SIZE; i++)
    res.value[i] = rand() % 256;
  res.value[0] &= 0x7F;
  return res;
}

GMac& GMac::cleanMac() {
  static uint8_t _value[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
  static GMac res(_value);
  return res;
}

GMac& GMac::broadcastMac() {
  static uint8_t _value[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
  static GMac res(_value);
  return res;
}
