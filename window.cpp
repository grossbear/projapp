
#ifdef __linux__
#include "xwin.cpp"
#elif _WIN32
#include "mswin.cpp"
#else
#error "Application window system not defined for other OS"
#endif
