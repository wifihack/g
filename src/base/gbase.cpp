#include "gbase.h"

#ifdef _DEBUG
const char* G_VERSION = "G Library version 0.1 Debug   Build( " __DATE__ " " __TIME__ " )";
#else // RELEASE
const char* G_VERSION = "G Library version 0.1 Release Build( " __DATE__ " " __TIME__ " )";
#endif // _DEBUG

unsigned long G_TIMEOUT = 10000; // 10 sec
