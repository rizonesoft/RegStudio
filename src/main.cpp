/**
 * RegStudio - Modern Windows Registry Editor
 * Copyright (c) 2026 Rizonesoft
 * 
 * Entry point for the application.
 */

#include <windows.h>
#include <commctrl.h>

// Forward declarations
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Application constants
constexpr const wchar_t* APP_CLASS_NAME = L"RegStudioMainWindow";
constexpr const wchar_t* APP_TITLE = L"RegStudio";
constexpr int DEFAULT_WIDTH = 1024;
constexpr int DEFAULT_HEIGHT = 768;

// Global instance handle
HINSTANCE g_hInstance = nullptr;

int WINAPI wWinMain(
    HINSTANCE hInstance,
    [[maybe_unused]] HINSTANCE hPrevInstance,
    [[maybe_unused]] LPWSTR lpCmdLine,
    int nCmdShow)
{
    g_hInstance = hInstance;

    // Initialize Common Controls (required for TreeView, ListView, etc.)
    INITCOMMONCONTROLSEX icex{};
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_WIN95_CLASSES | ICC_STANDARD_CLASSES;
    if (!InitCommonControlsEx(&icex)) {
        MessageBoxW(nullptr, L"Failed to initialize Common Controls", APP_TITLE, MB_ICONERROR);
        return 1;
    }

    // Register the window class
    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIconW(hInstance, MAKEINTRESOURCEW(1)); // IDI_APP from resource.rc
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wc.lpszClassName = APP_CLASS_NAME;
    wc.hIconSm = wc.hIcon;

    if (!RegisterClassExW(&wc)) {
        MessageBoxW(nullptr, L"Failed to register window class", APP_TITLE, MB_ICONERROR);
        return 1;
    }

    // Create the main window
    HWND hwnd = CreateWindowExW(
        0,                      // Optional window styles
        APP_CLASS_NAME,         // Window class
        APP_TITLE,              // Window text
        WS_OVERLAPPEDWINDOW,    // Window style
        CW_USEDEFAULT, CW_USEDEFAULT,  // Position
        DEFAULT_WIDTH, DEFAULT_HEIGHT, // Size
        nullptr,                // Parent window
        nullptr,                // Menu (will add later)
        hInstance,              // Instance handle
        nullptr                 // Additional application data
    );

    if (!hwnd) {
        MessageBoxW(nullptr, L"Failed to create main window", APP_TITLE, MB_ICONERROR);
        return 1;
    }

    // Show the window
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Message loop
    MSG msg{};
    while (GetMessageW(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_SIZE:
            // TODO: Resize child controls
            return 0;

        default:
            return DefWindowProcW(hwnd, uMsg, wParam, lParam);
    }
}
