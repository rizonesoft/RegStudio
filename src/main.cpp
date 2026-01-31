/**
 * RegStudio - Modern Windows Registry Editor
 * Copyright (c) 2026 Rizonesoft
 * 
 * Entry point for the application.
 */

#include <windows.h>
#include <commctrl.h>
#include <dwmapi.h>

// Link DWM library
#pragma comment(lib, "dwmapi.lib")

// Forward declarations
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ApplyDarkTitleBar(HWND hwnd);
void CreateMainMenu(HWND hwnd);

// Application constants
constexpr const wchar_t* APP_CLASS_NAME = L"RegStudioMainWindow";
constexpr const wchar_t* APP_TITLE = L"RegStudio";
constexpr int DEFAULT_WIDTH = 1024;
constexpr int DEFAULT_HEIGHT = 768;

// Menu IDs
constexpr UINT IDM_FILE_EXIT = 1001;
constexpr UINT IDM_EDIT_FIND = 2001;
constexpr UINT IDM_EDIT_COPY = 2002;
constexpr UINT IDM_EDIT_PASTE = 2003;
constexpr UINT IDM_VIEW_REFRESH = 3001;
constexpr UINT IDM_HELP_ABOUT = 4001;

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
    icex.dwICC = ICC_WIN95_CLASSES | ICC_STANDARD_CLASSES | ICC_TREEVIEW_CLASSES | ICC_LISTVIEW_CLASSES;
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
        nullptr,                // Menu (set via CreateMenu)
        hInstance,              // Instance handle
        nullptr                 // Additional application data
    );

    if (!hwnd) {
        MessageBoxW(nullptr, L"Failed to create main window", APP_TITLE, MB_ICONERROR);
        return 1;
    }

    // Apply modern styling
    ApplyDarkTitleBar(hwnd);
    CreateMainMenu(hwnd);

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

void ApplyDarkTitleBar(HWND hwnd) {
    // Force Dark Mode on Title Bar (Windows 10 Build 19041+)
    // DWMWA_USE_IMMERSIVE_DARK_MODE = 20
    BOOL value = TRUE;
    DwmSetWindowAttribute(hwnd, 20, &value, sizeof(value));
}

void CreateMainMenu(HWND hwnd) {
    HMENU hMenuBar = CreateMenu();
    
    // File menu
    HMENU hFileMenu = CreatePopupMenu();
    AppendMenuW(hFileMenu, MF_STRING, IDM_FILE_EXIT, L"E&xit\tAlt+F4");
    AppendMenuW(hMenuBar, MF_POPUP, reinterpret_cast<UINT_PTR>(hFileMenu), L"&File");
    
    // Edit menu
    HMENU hEditMenu = CreatePopupMenu();
    AppendMenuW(hEditMenu, MF_STRING, IDM_EDIT_FIND, L"&Find...\tCtrl+F");
    AppendMenuW(hEditMenu, MF_SEPARATOR, 0, nullptr);
    AppendMenuW(hEditMenu, MF_STRING, IDM_EDIT_COPY, L"&Copy\tCtrl+C");
    AppendMenuW(hEditMenu, MF_STRING, IDM_EDIT_PASTE, L"&Paste\tCtrl+V");
    AppendMenuW(hMenuBar, MF_POPUP, reinterpret_cast<UINT_PTR>(hEditMenu), L"&Edit");
    
    // View menu
    HMENU hViewMenu = CreatePopupMenu();
    AppendMenuW(hViewMenu, MF_STRING, IDM_VIEW_REFRESH, L"&Refresh\tF5");
    AppendMenuW(hMenuBar, MF_POPUP, reinterpret_cast<UINT_PTR>(hViewMenu), L"&View");
    
    // Help menu
    HMENU hHelpMenu = CreatePopupMenu();
    AppendMenuW(hHelpMenu, MF_STRING, IDM_HELP_ABOUT, L"&About RegStudio");
    AppendMenuW(hMenuBar, MF_POPUP, reinterpret_cast<UINT_PTR>(hHelpMenu), L"&Help");
    
    SetMenu(hwnd, hMenuBar);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case IDM_FILE_EXIT:
                    PostMessageW(hwnd, WM_CLOSE, 0, 0);
                    return 0;
                    
                case IDM_HELP_ABOUT:
                    MessageBoxW(hwnd, 
                        L"RegStudio v1.0.0\n\n"
                        L"A modern Windows Registry Editor\n\n"
                        L"Copyright © 2026 Rizonesoft",
                        L"About RegStudio",
                        MB_OK | MB_ICONINFORMATION);
                    return 0;
                    
                case IDM_VIEW_REFRESH:
                    // TODO: Refresh tree/list
                    return 0;
            }
            break;

        case WM_SIZE: {
            // Get new client area dimensions
            [[maybe_unused]] int width = LOWORD(lParam);
            [[maybe_unused]] int height = HIWORD(lParam);
            // TODO: Resize child controls (TreeView, ListView)
            return 0;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProcW(hwnd, uMsg, wParam, lParam);
    }
    return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}
