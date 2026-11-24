#ifndef APPLICATION_H
#define APPLICATION_H

#include "../input/InputDevice.h"
#include "../platform/windows/Window.h"

class Application
{
public:
    bool Initialize(HINSTANCE fucking_instance, int show_fucking_command);
    int Run();

private:
    InputDevice input_;
    Window window_{ input_ };
};

#endif // !APPLICATION_H