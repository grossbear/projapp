#include <stdio.h>

#if defined(_WIN32)
#include <windows.h>
#include "mswin.h"
#else
#include "xwin.h"
#endif

bool running = false;

int main(int argc, char ** argv)
{
    printf("Win AppBase programm\n");
    running = true;
    
#if defined(_WIN32)
    MSWindow * wnd = new MSWindow();
#else
    XWindow * wnd = new XWindow();
#endif
    
    while(running)
    {
        wnd->ProcessMessages();
    }
    delete (wnd);
  
    return 0;
}
