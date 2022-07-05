#ifndef UNICODE
#define UNICODE
#endif 
#include <Windows.h>
#include <windowsx.h>
#include <AudioDevice.h>
#include <cmath>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
unsigned int frequency = 80;
float amplitude = 0.0;
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    AudioDevice audioDevice;
    audioDevice.Start(frequency,amplitude);
    
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

                                        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        &audioDevice// Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    AudioDevice* device;
    switch (uMsg)
    {
    case WM_CREATE:
    {
        device = (AudioDevice*)((LPCREATESTRUCT)lParam)->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)device);
    }
    return 0;
    case WM_DESTROY:
    {
        device = (AudioDevice*)GetWindowLongPtr(hwnd,GWLP_USERDATA);
        device->Stop();

    PostQuitMessage(0);
    return 0; }
    case WM_MOUSEMOVE:
    {
        device = (AudioDevice*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        if (wParam&&MK_LBUTTON)
        {
            RECT rect;
            GetWindowRect(hwnd, &rect);
            int width = rect.right - rect.left;
            int height = rect.bottom - rect.top;
            int mouseX = GET_X_LPARAM(lParam);
            int mouseY = abs(GET_Y_LPARAM(lParam)-height);
            frequency = (unsigned int)( (float)mouseX / (float)width * 2000);
            amplitude = (float)mouseY / height;
            
        }
        else
        {
            amplitude = 0.0;
        }
        device->SetWaveParameters(frequency, amplitude);
        
    }
    return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}