#include <QString>
#include "gapp.h"

// ----------------------------------------------------------------------------
// GApp
// ----------------------------------------------------------------------------
void GApp::initialize() {
  qSetMessagePattern("[%{file}:%{line}] %{threadid} %{message}");
}
