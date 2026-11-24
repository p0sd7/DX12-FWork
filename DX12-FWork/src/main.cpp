#include "app/Application.h"

int WINAPI wWinMain(HINSTANCE fucking_instance, HINSTANCE, PWSTR, int show_fucking_command)
{
    Application app;

    if (!app.Initialize(fucking_instance, show_fucking_command))
        return 1;

    return app.Run();
}