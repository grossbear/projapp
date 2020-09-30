
#ifdef __linux__
#include "xwin.h"
#elif _WIN32
#include "mswin.h"
#else
#error "Application window system not defined for other OS"
#endif
