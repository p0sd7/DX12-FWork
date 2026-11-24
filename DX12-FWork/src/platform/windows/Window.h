#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>

class InputDevice;

class Window
{
public:
    explicit Window(InputDevice& fucking_input);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool Create(HINSTANCE fucking_instance, int show_fucking_command);
    HWND GetHandle() const;

private:
    static LRESULT CALLBACK WndProc(
        HWND hwnd, UINT fucking_message, WPARAM fucking_wParam, LPARAM fucking_lParam);

    LRESULT HandleMessage(
        HWND hwnd, UINT fucking_message, WPARAM fucking_wParam, LPARAM fucking_lParam);

    InputDevice& input_;
    HWND hwnd_ = nullptr;
};

#endif // !WINDOW_H