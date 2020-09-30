#pragma once
#include <windows.h>

class AppWindow
{
public:
    AppWindow();
    virtual ~AppWindow();
    
    void ProcessMessages();
    
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
    
private:
    bool CreateAppWindow();
    bool DestroyAppWindow();
    
    HWND hWnd;    
};

