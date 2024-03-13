#include "StickerManager.h"

HWND CreateSticker(HWND hParent, HINSTANCE hInstance, int x, int y, int width, int height)
{
    // Define the class name. Make sure this class is registered in WinMain.
    const wchar_t CLASS_NAME[] = L"ChildWindowClass";

    // Get the dimensions of the parent window
    RECT parentRect;
    GetWindowRect(hParent, &parentRect);

    // Calculate the desired position and size for the child window
    // For example, to place it 50 pixels to the right and 50 pixels down from the parent's top-left corner
    x = parentRect.left + 75;
    y = parentRect.top + 20;


    // Create the window.
    HWND hwndSticker = CreateWindowEx(
        0,                 // Optional window styles.
        CLASS_NAME,        // Window class
        L"Child Window",   // Window text
        WS_VISIBLE | WS_CHILD, // Window style
        x, y, width, height,   // Size and position
        hParent,           // Parent window    
        NULL,              // Menu
        hInstance,         // Instance handle
        NULL   // Additional application data
    );

    // The message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return hwndSticker;
}

LRESULT CALLBACK StickerWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    RECT rcClient;
    GetClientRect(hWnd, &rcClient);

    int width = rcClient.right - rcClient.left;
    int height = rcClient.bottom - rcClient.top;

    static HBITMAP hbmSticker = NULL;

    switch (uMsg)
    {
    case WM_CREATE: // where you create all the interface
    {
        break;
    }
    case WM_COMMAND: // Button logic
    {
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        HDC hdcMem = CreateCompatibleDC(hdc);

        HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, L"C:\\Users\\Snawy\\source\\repos\\Snawyyy\\Pixel_Letter_Station\\Images\\LOGO.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
        if (hBitmap == NULL)
        {
            MessageBox(NULL, L"Load Failed", L"Fail", MB_OK);
        }
        hdcMem = CreateCompatibleDC(hdc);
        HGDIOBJ oldBitmap = SelectObject(hdcMem, hBitmap);

        BITMAP bitmap;
        GetObject(hBitmap, sizeof(BITMAP), &bitmap);
        StretchBlt(hdc, SMALL_MARGIN + BORDER_EFFECT_SIZE, (WIN_BAR_SIZE / 2) - ((bitmap.bmHeight / 2) / 2), (bitmap.bmWidth / 2), (bitmap.bmHeight / 2), hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DRAWITEM:
    {

        break;
    }
    case WM_ERASEBKGND:
    {
        return 1;
    }
    case WM_NCHITTEST: // Window Dragging logic
    {
        // Convert the mouse position to screen coordinates
        POINT pt = { LOWORD(lParam), HIWORD(lParam) };
        ScreenToClient(hWnd, &pt);

        // Define the draggable area, e.g., top 50 pixels of the window
        RECT draggableArea = { 0, 0, width, height}; // You need to define windowWidth

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
    case WM_CLOSE: {
        DestroyWindow(hWnd);
        return 0;
    }
    case WM_DESTROY: {
        // Cleanup: the bitmap we didn't delete gets deleted
        if (hbmSticker != NULL) {
            DeleteObject(hbmSticker);
            hbmSticker = NULL;
        }
        return 0;
    }
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}