#include "Sticker.h"

HWND g_hwndSticker = NULL;

HWND CreateSticker(HWND hParent, HINSTANCE hInstance, int x, int y, int height, HBITMAP hbmSticker)
{
    // Define the class name. Make sure this class is registered in WinMain.
    const wchar_t CLASS_NAME[] = L"StickerWindowClass";

    // Load the bitmap to get its dimensions
    if (hbmSticker == NULL)
    {
        MessageBox(NULL, L"Load Failed", L"Fail", MB_OK);
        return NULL;
    }

    BITMAP bitmap;
    GetObject(hbmSticker, sizeof(BITMAP), &bitmap);

  
    // Calculate the new width based on the aspect ratio and the desired height
    int width = (bitmap.bmWidth * height) / bitmap.bmHeight;

    // Calculate the desired position and size for the child window
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    ScreenToClient(hParent, &cursorPos);

    // bug doesn't work with 2 clients
    x = cursorPos.x - (width / 2);
    y = cursorPos.y - (height / 2);

    // Delete the bitmap since it's no longer needed
    DeleteObject(hbmSticker);

    // Create the window.
    HWND hwndSticker = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Sticker",
        WS_VISIBLE | WS_CHILD | CS_OWNDC | CS_HREDRAW | CS_VREDRAW | WS_CLIPSIBLINGS,
        x, y, width, height,
        hParent,
        NULL,
        hInstance,
        NULL
    );

    SetWindowPos(hwndSticker, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    g_hwndSticker = hwndSticker;

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

        HBITMAP hbmSticker = (HBITMAP)LoadImage(NULL, L"C:\\Users\\Snawy\\source\\repos\\Snawyyy\\Pixel_Letter_Station\\Images\\LOGO.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
        if (hbmSticker == NULL)
        {
            MessageBox(NULL, L"Load Failed", L"Fail", MB_OK);
            EndPaint(hWnd, &ps);
            return 0;
        }

        HGDIOBJ oldBitmap = SelectObject(hdcMem, hbmSticker);

        BITMAP bitmap;
        GetObject(hbmSticker, sizeof(BITMAP), &bitmap);

        // Create a bitmap with a transparent background
        HBITMAP hbmTransparent = CreateBitmap(width, height, 1, 32, NULL);
        HDC hdcTransparent = CreateCompatibleDC(hdc);
        HGDIOBJ oldTransparentBitmap = SelectObject(hdcTransparent, hbmTransparent);

        // Fill the transparent bitmap with a fully transparent color
        FillRect(hdcTransparent, &rcClient, (HBRUSH)GetStockObject(NULL_BRUSH));

        // Draw the sticker bitmap onto the transparent bitmap
        StretchBlt(hdcTransparent, 0, 0, width, height, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

        // Draw the transparent bitmap onto the window DC
        BitBlt(hdc, 0, 0, width, height, hdcTransparent, 0, 0, SRCCOPY);

        // Clean up
        SelectObject(hdcTransparent, oldTransparentBitmap);
        DeleteObject(hbmTransparent);
        DeleteDC(hdcTransparent);

        SelectObject(hdcMem, oldBitmap);
        DeleteDC(hdcMem);

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DRAWITEM:
    {

        break;
    }
    case WM_RBUTTONDOWN:
    {
        DestroyWindow(hWnd);
        return 0;
        break;
    }
    case WM_NCHITTEST: // Window Dragging logic
    {
        // Convert the mouse position to screen coordinates
        POINT pt = { LOWORD(lParam), HIWORD(lParam) };
        ScreenToClient(hWnd, &pt);

        // Define the draggable area
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