#include "Application.h"

bool Application::Initialize(HINSTANCE fucking_instance, int show_fucking_command)
{
    return window_.Create(fucking_instance, show_fucking_command);
}

int Application::Run()
{
    MSG message{};

    while (true)
    {
        while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE))
        {
            if (message.message == WM_QUIT)
                return static_cast<int>(message.wParam);

            TranslateMessage(&message);
            DispatchMessageW(&message);
        }

        const wchar_t* title = L"DX12 FWork";

        if (input_.IsKeyDown('W'))
            title = L"DX12 FWork | fucking W pressed";
        else if (input_.IsKeyDown(VK_LBUTTON))
            title = L"DX12 FWork | fucking left mouse button pressed";

        SetWindowTextW(window_.GetHandle(), title);
        WaitMessage();
    }
}