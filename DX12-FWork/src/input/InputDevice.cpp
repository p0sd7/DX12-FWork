#include "InputDevice.h"

void InputDevice::SetKeyDown(unsigned int fucking_key, bool is_fucking_down)
{
    if (fucking_key < keys_.size())
        keys_[fucking_key] = is_fucking_down;
}

bool InputDevice::IsKeyDown(unsigned int fucking_key) const
{
    return fucking_key < keys_.size() && keys_[fucking_key];
}

void InputDevice::ResetKeys()
{
    keys_.fill(false);
}

void InputDevice::SetMousePosition(int x, int y)
{
    mouseX_ = x;
    mouseY_ = y;
}

int InputDevice::GetMouseX() const
{
    return mouseX_;
}

int InputDevice::GetMouseY() const
{
    return mouseY_;
}