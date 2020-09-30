#pragma once
#include "window.h"

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
    bool running;
    AppWindow * window;
};
