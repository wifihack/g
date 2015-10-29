#include <QString>
#include "gapp.h"

// ----------------------------------------------------------------------------
// GApp
// ----------------------------------------------------------------------------
void GApp::init() {
  qSetMessagePattern("%{time yyyyMMdd h:mm:ss.zzz t} [%{file}:%{line}] %{threadid} %{message}");
}
