#include "Letter.h"
#include "CustomWindowUI.h"

HBITMAP GetLetter(HWND hWnd)
{
    HDC hdcWindow = GetDC(hWnd);
    HDC hdcMemDC = CreateCompatibleDC(hdcWindow);

    RECT rcClient;
    GetClientRect(hWnd, &rcClient);
    int width = rcClient.right - rcClient.left;
    int height = rcClient.bottom - rcClient.top;

    HBITMAP hbmScreen = CreateCompatibleBitmap(hdcWindow, width, height);
    HGDIOBJ oldBitmap = SelectObject(hdcMemDC, hbmScreen);

    BitBlt(hdcMemDC, 0, 0, width, height, hdcWindow, 0, 0, SRCCOPY);

    // Cleanup: Only delete the memory DC and release the window DC.
    SelectObject(hdcMemDC, oldBitmap); // Restore the old bitmap
    DeleteDC(hdcMemDC);
    ReleaseDC(hWnd, hdcWindow);

    // Return the created bitmap
    return hbmScreen;
}

HWND CreateLetterWindow(HWND hParent, HINSTANCE hInstance, int x, int y, int width, int height)
{
    // Define the class name. Make sure this class is registered in WinMain.
    const wchar_t CLASS_NAME[] = L"ChildWindowClass";

    // Create the window.
    HWND hwndLetter = CreateWindowEx(
        0,                 // Optional window styles.
        CLASS_NAME,        // Window class
        L"Child Window",   // Window text
        WS_VISIBLE | WS_POPUP, // Window style
        x, y, width, height,   // Size and position
        hParent,           // Parent window    
        NULL,              // Menu
        hInstance,         // Instance handle
        NULL               // Additional application data
    );

    return hwndLetter;
}

LRESULT CALLBACK LetterWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    RECT rcClient;
    GetClientRect(hWnd, &rcClient);
    int width = rcClient.right - rcClient.left;
    int height = rcClient.bottom - rcClient.top;

    switch (uMsg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        HDC hdcMem = CreateCompatibleDC(hdc);

        WindowBar(hdc, hWnd, width);

        HBITMAP hbmScreen = GetLetter(GetParent(hWnd));
        HGDIOBJ oldBitmap = SelectObject(hdcMem, hbmScreen); // Use the bitmap handle

        // Get bitmap dimensions
        BITMAP bitmap;
        GetObject(hbmScreen, sizeof(bitmap), &bitmap);

        // Draw the bitmap
        BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);

        // Cleanup
        SelectObject(hdcMem, oldBitmap);
        DeleteDC(hdcMem);
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_NCHITTEST: // Window Dragging logic
    {
        // Convert the mouse position to screen coordinates
        POINT pt = { LOWORD(lParam), HIWORD(lParam) };
        ScreenToClient(hWnd, &pt);

        // Define the draggable area, e.g., top 50 pixels of the window
        RECT draggableArea = { 0, 0, width, WIN_BAR_SIZE }; // You need to define windowWidth

        // Check if the point is within the draggable area
        if (PtInRect(&draggableArea, pt))
        {
            return HTCAPTION;
        }
        else
        {
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    }
    case WM_CLOSE:
    {
        return DestroyWindow(hWnd);
        break;
    }
    case WM_DESTROY:
    {
        KillTimer(hWnd, 1);
        PostQuitMessage(0);
        return 0;
    }
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}