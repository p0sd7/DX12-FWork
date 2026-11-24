#ifndef INPUT_DEVICE_H
#define INPUT_DEVICE_H

#include <array>

class InputDevice
{
public:
    void SetKeyDown(unsigned int fucking_key, bool is_fucking_down);
    bool IsKeyDown(unsigned int fucking_key) const;
    void ResetKeys();

    void SetMousePosition(int x, int y);
    int GetMouseX() const;
    int GetMouseY() const;

private:
    std::array<bool, 256> keys_{};
    int mouseX_ = 0;
    int mouseY_ = 0;
};

#endif // !INPUT_DEVICE_H
