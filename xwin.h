#pragma once

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include <sys/utsname.h>


class AppWindow
{
public:
    AppWindow();
    virtual ~AppWindow();
    
    void ProcessMessages();
    
    
private:
    bool CreateAppWindow();
    bool DestroyAppWindow();

    Display * display;
    Window winId;

    bool uname_ok;
    Atom WM_DELETE_WINDOW; 
};
