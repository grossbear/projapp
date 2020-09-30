#include <stdio.h>
#include "mswin.h"

extern bool running;

MSWindow::MSWindow():
hWnd(NULL)
{
    printf("Window constructor\n");
    CreateDisplayWindow();
}

MSWindow::~MSWindow()
{
    printf("Window destructor\n");
    DestroyDisplayWindow();
}

void MSWindow::ProcessMessages()
{
    MSG msg;
    if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))    // Is There A Message Waiting?
    {
        TranslateMessage(&msg);                 // Translate The Message
        DispatchMessage(&msg);                  // Dispatch The Message
    }
}

LRESULT CALLBACK MSWindow::WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message) {
		
		// Upon destruction, tell the main thread to stop 
		case WM_DESTROY: {
			PostQuitMessage(0);
			running = false;
			break;
		}
		
		// All other messages (a lot of them) are processed using default procedures 
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

bool MSWindow::CreateDisplayWindow()
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    
    WNDCLASSEX wc; // A properties struct of our window  
	MSG Msg; // A temporary location for all messages  

	// zero out the struct and set the stuff we want to modify  
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = MSWindow::WndProc; // This is where we will send messages to 
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	// White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it  
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); // Load a standard icon  
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); // use the name "A" to use the project icon  

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return false;
	}

	hWnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","AppBase",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, // x  
		CW_USEDEFAULT, // y  
		640, // width  
		480, // height  
		NULL,NULL,hInstance,NULL);

	if(hWnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return false;
	}
	
	return true;
}

bool MSWindow::DestroyDisplayWindow()
{
    HINSTANCE hInstance = GetModuleHandle(NULL);
    if(hWnd)
    {
        DestroyWindow( hWnd );
        UnregisterClass( "WindowClass", hInstance );
        return true;
    }
    return false;
}


