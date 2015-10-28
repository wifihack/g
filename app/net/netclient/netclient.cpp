#include <QApplication>
#include "widget.h"

#include <QSsl>

Q_DECLARE_METATYPE(QSsl::SslProtocol)

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  Widget w;
  w.show();
  return a.exec();
}
