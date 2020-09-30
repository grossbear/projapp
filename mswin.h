#pragma once
#include <windows.h>
#include "appbase.h"

class MSWindow
{
public:
    MSWindow();
    virtual ~MSWindow();
    
    void ProcessMessages();
    
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
    
private:
    bool CreateDisplayWindow();
    bool DestroyDisplayWindow();
    
    HWND hWnd;    
};
