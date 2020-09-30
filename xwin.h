#pragma once

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include <sys/utsname.h>

#include "appbase.h"

class XWindow
{
public:
    XWindow();
    virtual ~XWindow();
    
    void ProcessMessages();
    
    
private:
    bool CreateDisplayWindow();
    bool DestroyDisplayWindow();

    Display * display;
    Window winId;

    bool uname_ok;
    Atom WM_DELETE_WINDOW; 
};
