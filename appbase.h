#pragma once

#if defined(_WIN32)
#include "mswin.h"
#endif

class AppBase
{
public:
    virtual ~AppBase();
    static AppBase * CreateSingleton();
    static AppBase * GetSingleton();
    
    void Run();
    void CloseApp();
    
protected:
    AppBase();
    
private:
    static AppBase * app;
};
