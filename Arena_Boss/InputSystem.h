#pragma once

#include "Common.h"
#include <dinput.h>
#include <memory>
#include "Vector2.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

enum class Key : byte
{
    A = DIK_A,
    B = DIK_B,
    C = DIK_C,
    D = DIK_D,
    E = DIK_E,
    F = DIK_F,
    G = DIK_G,
    H = DIK_H,
    I = DIK_I,
    J = DIK_J,
    K = DIK_K,
    L = DIK_L,
    M = DIK_M,
    N = DIK_N,
    O = DIK_O,
    P = DIK_P,
    Q = DIK_Q,
    R = DIK_R,
    S = DIK_S,
    T = DIK_T,
    U = DIK_U,
    V = DIK_V,
    W = DIK_W,
    X = DIK_X,
    Y = DIK_Y,
    Z = DIK_Z,
    Z = DIK_Z,

    Up = DIK_UP,
    Down = DIK_DOWN,
    Left = DIK_LEFT,
    Right = DIK_RIGHT,

    Num0 = DIK_0,
    Num1 = DIK_1,
    Num2 = DIK_2,
    Num3 = DIK_3,
    Num4 = DIK_4,
    Num5 = DIK_5,
    Num6 = DIK_6,
    Num7 = DIK_7,
    Num8 = DIK_8,
    Num9 = DIK_9,

    F1 = DIK_F1,
    F2 = DIK_F2,
    F3 = DIK_F3,
    F4 = DIK_F4,
    F5 = DIK_F5,
    F6 = DIK_F6,
    F7 = DIK_F7,
    F8 = DIK_F8,
    F9 = DIK_F9,
    F10 = DIK_F10,
    F11 = DIK_F11,
    F12 = DIK_F12,

    Numpad0 = DIK_NUMPAD0,
    Numpad1 = DIK_NUMPAD1,
    Numpad2 = DIK_NUMPAD2,
    Numpad3 = DIK_NUMPAD3,
    Numpad4 = DIK_NUMPAD4,
    Numpad5 = DIK_NUMPAD5,
    Numpad6 = DIK_NUMPAD6,
    Numpad7 = DIK_NUMPAD7,
    Numpad8 = DIK_NUMPAD8,
    Numpad9 = DIK_NUMPAD9,

    Plus = DIK_ADD,
    Minus = DIK_SUBTRACT,
    Multiply = DIK_MULTIPLY,
    Divide = DIK_DIVIDE,
    Decimal = DIK_DECIMAL,

    NumpadEnter = DIK_NUMPADENTER,

    Esc = DIK_ESCAPE,
    Enter = DIK_RETURN,
    Space = DIK_SPACE,
    BackSpace = DIK_BACK,
    Tab = DIK_TAB,
    Menu = DIK_APPS,
    CapsLock = DIK_CAPITAL,
    NumLock = DIK_NUMLOCK,
    ScrollLock = DIK_SCROLL,
    LeftCtrl = DIK_LCONTROL,
    RightCtrl = DIK_RCONTROL,
    LeftShift = DIK_LSHIFT,
    RightShift = DIK_RSHIFT,
    LeftAlt = DIK_LMENU,
    RightAlt = DIK_RMENU,
    LeftWindows = DIK_LWIN,
    RightWindows = DIK_RWIN,

    LeftBracket = DIK_LBRACKET,
    RightBracket = DIK_RBRACKET,

    Dash = DIK_MINUS,
    Equals = DIK_EQUALS,

    Slash = DIK_SLASH,
    BackSlash = DIK_BACKSLASH,
    Peroid = DIK_PERIOD,
    Comma = DIK_COMMA,
    Semicolon = DIK_SEMICOLON,
    Apostrophe = DIK_APOSTROPHE,
    Grave = DIK_GRAVE,

    Print = DIK_SYSRQ,
    Pause = DIK_PAUSE,

    Insert = DIK_INSERT,
    Delete = DIK_DELETE,
    Home = DIK_HOME,
    End = DIK_END,
    PageUp = DIK_PRIOR,
    PageDown = DIK_NEXT,

    MouseLeft = 0xFD,
    MouseRight = 0xFE,
    MouseMiddle = 0xFF,
};

class InputSystem
{
public:
    InputSystem(HINSTANCE hInstance, HWND hWnd, int width, int height);

    InputSystem(const InputSystem&) = delete;
    InputSystem(InputSystem&&) = default;

    InputSystem& operator=(const InputSystem&) = delete;
    InputSystem& operator=(InputSystem&&) = default;

    ~InputSystem();

    inline bool Update()
    {
        return ReadKeyboard() && ReadMouse() && ProcessInput();
    }

    inline bool IsButtonDown(Key key) const noexcept
    {
        return IsCurDown(key);
    }

    inline bool IsButtonUp(Key key) const noexcept
    {
        return !IsCurDown(key);
    }

    inline bool IsButtonPress(Key key) const noexcept
    {
        return IsCurDown && !IsOldDown(key);
    }

    inline bool IsButtonRelease(Key key) const noexcept
    {
        return !IsCurDown && IsOldDown(key);
    }

    inline Math::Vector2 GetMousePos() const noexcept
    {
        return Math::Vector2{ curMouseState.lX, curMouseState.lY };
    }

    inline Math::Vector2 GetMouseMove() const noexcept
    {
        return Math::Vector2{ curMouseState.lX - oldMouseState.lX, curMouseState.lY - oldMouseState.lY };
    }

    inline int GetWheelPos() const noexcept
    {
        return curMouseState.lZ;
    }

    inline int GetWheelMove() const noexcept
    {
        return curMouseState.lZ - oldMouseState.lZ;
    }

private:
    bool ReadKeyboard();
    bool ReadMouse();
    bool ProcessInput();

    bool IsCurDown(Key key) const noexcept;
    bool IsOldDown(Key key) const noexcept;

private:
    IDirectInput8* input = nullptr;
    IDirectInputDevice8* keyboard = nullptr;
    IDirectInputDevice8* mouse = nullptr;

    byte curKeyState[256];
    byte oldKeyState[256];
    DIMOUSESTATE2 curMouseState;
    DIMOUSESTATE2 oldMouseState;
    int screenWidth = 0;
    int screenHeight = 0;
    int mouseX = 0;
    int mouseY = 0;
};