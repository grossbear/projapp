#include "appbase.h"

AppBase * AppBase::app = NULL;

AppBase * AppBase::CreateSingleton()
{
    if(app == NULL)
        app = new AppBase();
        
    return app;
}

AppBase * AppBase::GetSingleton()
{
    return app;
}

AppBase::AppBase():
running(false),window(NULL)
{
    window = new AppWindow();
    running = true;
}

AppBase::~AppBase()
{
    running = false;
    delete (window);
    window = NULL;
}

void AppBase::Run()
{
    while(running)
    {
        window->ProcessMessages();
    }
}

void AppBase::CloseApp()
{
    running = false;
}
