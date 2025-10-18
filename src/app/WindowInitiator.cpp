#include "WindowInitiator.hpp"
#include <windows.h>

LRESULT CALLBACK HandleWindowMessages(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void WindowInitiator::createWindow() {
    const char* windowTitle = "Screen"; // <-- Changed window title
    const char* className = "BlackWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = HandleWindowMessages;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = className;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        className,
        windowTitle,
        WS_POPUP | WS_VISIBLE,
        0, 0,
        GetSystemMetrics(SM_CXSCREEN),
        GetSystemMetrics(SM_CYSCREEN),
        nullptr,
        nullptr,
        GetModuleHandle(nullptr),
        nullptr
    );

    ShowCursor(false);  // Hide cursor
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK HandleWindowMessages(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CLOSE:
        case WM_KEYDOWN:
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_ERASEBKGND: {
            RECT clientRect;
            GetClientRect(hwnd, &clientRect);
            FillRect(reinterpret_cast<HDC>(wParam), &clientRect, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
            return 1;
        }

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}
