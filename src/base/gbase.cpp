#include "gbase.h"

namespace g {

#ifdef _DEBUG
const char* VERSION = "G Library version 0.1 Debug   Build( " __DATE__ " " __TIME__ " )";
#else // RELEASE
const char* VERSION = "G Library version 0.1 Release Build( " __DATE__ " " __TIME__ " )";
#endif // _DEBUG

}
