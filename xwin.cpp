#include <stdio.h>
#include "xwin.h"
#include "appbase.h"


AppWindow::AppWindow():
winId(0),display(NULL),uname_ok(false)
{
    printf("window constructor\n");
    CreateAppWindow();
}

AppWindow::~AppWindow()
{
    printf("window destructor\n");
    DestroyAppWindow();
}

void AppWindow::ProcessMessages()
{
    XEvent e;
    XNextEvent(display, &e);
    if (e.type == Expose) 
    {
      int y_offset = 20;
      int s = DefaultScreen(display);
      struct utsname sname;  
 
#if defined(__APPLE_CC__)  
      const char* s1 = "X11 test app under Mac OS X Lion";
#else      
      const char* s1 = "X11 test app under Linux";
#endif      
 
      const char* s2 = "(C)2012 Geeks3D.com"; 
      XDrawString(display, winId, DefaultGC(display, s), 10, y_offset, s1, strlen(s1));
      y_offset += 20;
      XDrawString(display, winId, DefaultGC(display, s), 10, y_offset, s2, strlen(s2));
      y_offset += 20;
 
      if (uname_ok)
      {
        char buf[256] = {0};
 
        sprintf(buf, "System information:");
        XDrawString(display, winId, DefaultGC(display, s), 10, y_offset, buf, strlen(buf));
        y_offset += 15;
 
        sprintf(buf, "- System: %s", sname.sysname);
        XDrawString(display, winId, DefaultGC(display, s), 10, y_offset, buf, strlen(buf));
        y_offset += 15;
 
        sprintf(buf, "- Release: %s", sname.release);
        XDrawString(display, winId, DefaultGC(display, s), 10, y_offset, buf, strlen(buf));
        y_offset += 15;
 
        sprintf(buf, "- Version: %s", sname.version);
        XDrawString(display, winId, DefaultGC(display, s), 10, y_offset, buf, strlen(buf));
        y_offset += 15;
 
        sprintf(buf, "- Machine: %s", sname.machine);
        XDrawString(display, winId, DefaultGC(display, s), 10, y_offset, buf, strlen(buf));
        y_offset += 20;
      }
 
 
      //DisplayWindowAttributes wa;
      //XGetWindowAttributes(display, winId, &wa);
      //int width = wa.width;
      //int height = wa.height;
      //char buf[128]={0};
      //sprintf(buf, "Current window size: %dx%d", width, height);
      //XDrawString(display, winId, DefaultGC(display, s), 10, y_offset, buf, strlen(buf));
      //y_offset += 20;
    }
 
    if (e.type == KeyPress)
    {
      char buf[128] = {0};
      KeySym keysym;
      int len = XLookupString(&e.xkey, buf, sizeof buf, &keysym, NULL);
      if (keysym == XK_Escape)
      {
	AppBase * app = AppBase::GetSingleton();
        app->CloseApp();
      }
    }
 
    if ((e.type == ClientMessage) && 
        (static_cast<unsigned int>(e.xclient.data.l[0]) == WM_DELETE_WINDOW))
    {
	AppBase * app = AppBase::GetSingleton();
        app->CloseApp();
    }
}


bool AppWindow::CreateAppWindow()
{
  display = XOpenDisplay(NULL);
  if (display == NULL) 
  {
    fprintf(stderr, "Cannot open display\n");
    exit(1);
  }
 
  int s = DefaultScreen(display);
  winId = XCreateSimpleWindow(display, RootWindow(display, s), 10, 10, 660, 200, 1,
                                   BlackPixel(display, s), WhitePixel(display, s));
  XSelectInput(display, winId, ExposureMask | KeyPressMask);
  XMapWindow(display, winId);
 
  XStoreName(display, winId, "Geeks3D.com - X11 window under Linux (Mint 10)");
 
  WM_DELETE_WINDOW = XInternAtom(display, "WM_DELETE_WINDOW", False); 
  XSetWMProtocols(display, winId, &WM_DELETE_WINDOW, 1);  
 
  uname_ok = false;
  struct utsname sname;  
  int ret = uname(&sname);
  if (ret != -1)
  {
    uname_ok = true;
  }
 
	return true;
}

bool AppWindow::DestroyAppWindow()
{
    XDestroyWindow(display, winId);
    XCloseDisplay(display);
    
    display = NULL;
    winId = 0;
    return true;
}

