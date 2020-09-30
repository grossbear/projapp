#include <stdio.h>
#include "appbase.h"

int main(int argc, char ** argv)
{
    printf("Win AppBase programm\n");
    AppBase * app = AppBase::CreateSingleton();
    app->Run();
    delete (app);
  
    return 0;
}

