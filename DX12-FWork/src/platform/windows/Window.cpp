#include "Window.h"
#include "../../input/InputDevice.h"

#include <windowsx.h> 

Window::Window(InputDevice& fucking_input)
    : input_(fucking_input)
{
}

Window::~Window()
{
    if (hwnd_)
        DestroyWindow(hwnd_);
}

bool Window::Create(HINSTANCE fucking_instance, int show_fucking_command)
{
    constexpr wchar_t className[] = L"Dx12FrameworkWindow";
    constexpr DWORD style = WS_OVERLAPPEDWINDOW;

    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = &Window::WndProc;
    wc.hInstance = fucking_instance;
    wc.hCursor = LoadCursorW(nullptr, MAKEINTRESOURCEW(32512));
    wc.hbrBackground = GetSysColorBrush(COLOR_WINDOW);
    wc.lpszClassName = className;

    if (!RegisterClassExW(&wc))
        return false;

    RECT rect{ 0, 0, 800, 600 };
    if (!AdjustWindowRect(&rect, style, FALSE))
        return false;

    hwnd_ = CreateWindowExW(
        0,
        className,
        L"DX12 FWork",
        style,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right - rect.left,
        rect.bottom - rect.top,
        nullptr,
        nullptr,
        fucking_instance,
        this
    );

    if (!hwnd_)
        return false;

    ShowWindow(hwnd_, show_fucking_command);
    UpdateWindow(hwnd_);
    return true;
}

HWND Window::GetHandle() const
{
    return hwnd_;
}

LRESULT CALLBACK Window::WndProc(
    HWND hwnd, UINT fucking_message, WPARAM fucking_wParam, LPARAM lParam)
{
    Window* window = nullptr;

    if (fucking_message == WM_NCCREATE)
    {
        auto* createInfo = reinterpret_cast<CREATESTRUCTW*>(lParam);
        window = static_cast<Window*>(createInfo->lpCreateParams);

        SetWindowLongPtrW(
            hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
    }
    else
    {
        window = reinterpret_cast<Window*>(
            GetWindowLongPtrW(hwnd, GWLP_USERDATA));
    }

    if (window)
        return window->HandleMessage(hwnd, fucking_message, fucking_wParam, lParam);

    return DefWindowProcW(hwnd, fucking_message, fucking_wParam, lParam);
}

LRESULT Window::HandleMessage(
    HWND hwnd, UINT fucking_message, WPARAM fucking_wParam, LPARAM lParam)
{
    switch (fucking_message)
    {
    case WM_KEYDOWN:
    case WM_KEYUP:
        input_.SetKeyDown(
            static_cast<unsigned int>(fucking_wParam), fucking_message == WM_KEYDOWN);
        return 0;

    case WM_MOUSEMOVE:
        input_.SetMousePosition(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        return 0;

    case WM_LBUTTONDOWN:
        SetCapture(hwnd);
        input_.SetKeyDown(VK_LBUTTON, true);
        return 0;

    case WM_LBUTTONUP:
        input_.SetKeyDown(VK_LBUTTON, false);
        ReleaseCapture();
        return 0;

    case WM_CAPTURECHANGED:
        input_.SetKeyDown(VK_LBUTTON, false);
        return 0;

    case WM_KILLFOCUS:
        input_.ResetKeys();
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_NCDESTROY:
        hwnd_ = nullptr;
        SetWindowLongPtrW(hwnd, GWLP_USERDATA, 0);
        break;
    }

    return DefWindowProcW(hwnd, fucking_message, fucking_wParam, lParam);
}