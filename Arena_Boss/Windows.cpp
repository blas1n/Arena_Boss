#include "Windows.h"
#include "FileSystem.h"
#include "Util.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

Windows::Windows(const tstring& title, uint32_t width, uint32_t height)
    : programPath(FileSystem::GetCurrentPath()),
    hInstance(GetModuleHandle(nullptr)),
    windowTitle(title)
{
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEXA);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = nullptr;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND + 1);
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = windowClassName.c_str();
    wc.hIconSm = nullptr;

    assert(RegisterClassEx(&wc));

    DWORD style = 0;
    style |= WS_VISIBLE;
    style &= ~WS_SIZEBOX;

    RECT winRect = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
    if (!AdjustWindowRect(&winRect, style, FALSE))
    {
        UnregisterClass(windowClassName.c_str(), hInstance);
        assert(false);
    }

    const auto resolution = Math::Vector2
    {
        static_cast<float>(GetSystemMetrics(SM_CXSCREEN)),
        static_cast<float>(GetSystemMetrics(SM_CYSCREEN))
    };

    size.SetX(static_cast<float>(winRect.right - winRect.left));
    size.SetX(static_cast<float>(winRect.bottom - winRect.top));
    pos = (resolution - size) / 2;
    center = resolution / 2;

    hWnd = CreateWindow(
        windowClassName.c_str(),
        windowTitle.c_str(),
        style,
        static_cast<int>(pos.GetX()),
        static_cast<int>(pos.GetY()),
        static_cast<int>(size.GetX()),
        static_cast<int>(size.GetY()),
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (!hWnd)
    {
        UnregisterClass(windowClassName.c_str(), hInstance);
        assert(false);
    }

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);
    SetForegroundWindow(hWnd);
    SetFocus(hWnd);

    UpdateClientPos();
}

Windows::~Windows()
{
    if (hWnd)
        DestroyWindow(hWnd);

    UnregisterClass(windowClassName.c_str(), hInstance);
}

void Windows::UpdateClientPos()
{
    RECT rect;
    GetClientRect(hWnd, &rect);

    POINT LT{ rect.left, rect.top };
    POINT RB{ rect.right, rect.bottom };

    ClientToScreen(hWnd, &LT);
    ClientToScreen(hWnd, &RB);

    pos = LT;
    size = RB;
    size -= LT;
    center = pos + (size / 2);
}

void Windows::DoEvents()
{
    MSG msg;
    
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}