#include "Sticker.h"

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

    // bug doesn't work with 2 clients
    x = cursorPos.x - (width / 2);
    y = cursorPos.y - (height / 2);

    // Create the window.
    HWND hwndSticker = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Sticker",
        WS_VISIBLE | WS_POPUP | WS_CLIPSIBLINGS,
        x, y, width, height,
        hParent,
        NULL,
        hInstance,
        (LPVOID)hbmSticker
    );

    SetWindowPos(hwndSticker, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    return hwndSticker;
}

LRESULT CALLBACK StickerWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    RECT rcClient;
    GetClientRect(hWnd, &rcClient);

    int width = rcClient.right - rcClient.left;
    int height = rcClient.bottom - rcClient.top;

    static HBITMAP hbmSticker = NULL;

    HWND hWndParent = GetParent(hWnd);

    // get Client top left coordinates in relation to screen
    POINT screenCords = { 0, 0 };
    ClientToScreen(hWnd, &screenCords);

    // get parent client for limiting sticker to bounds
    RECT parentClientRect;
    GetClientRect(GetParent(hWnd), &parentClientRect);

    MapWindowPoints(hWndParent, NULL, (LPPOINT)&parentClientRect, 2);
    int parentWidth = parentClientRect.right - parentClientRect.left;
    int parentHeight = parentClientRect.bottom - parentClientRect.top;


    static bool isDragging = false;


    switch (uMsg)
    {
    case WM_CREATE: // where you create all the interface
    {
        CREATESTRUCT* pCreateStruct = (CREATESTRUCT*)lParam;
        hbmSticker = (HBITMAP)pCreateStruct->lpCreateParams;

        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)hbmSticker);
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

        hbmSticker = (HBITMAP)GetWindowLongPtr(hWnd, GWLP_USERDATA);
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
    case WM_MOUSEMOVE:
    {
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(TRACKMOUSEEVENT);
        tme.dwFlags = TME_LEAVE; // Specifies that we want a WM_MOUSELEAVE message when the mouse leaves
        tme.hwndTrack = hWnd;
        tme.dwHoverTime = HOVER_DEFAULT; // Not needed for WM_MOUSELEAVE but required to be set

        TrackMouseEvent(&tme); // Call this function to start tracking

        POINT cursorPos;
        GetCursorPos(&cursorPos);
        if (isDragging)
        {
            SetWindowPos(hWnd, NULL, cursorPos.x - width / 2, cursorPos.y - height / 2, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
        }

        break;
    }
    case WM_LBUTTONDOWN:
    {
    isDragging = true;

    // Set the capture to the window
    SetCapture(hWnd);
    break;
    }
    case WM_LBUTTONUP:
    {
    isDragging = false;

    // Release the capture
    ReleaseCapture();
    break;
    }
    case WM_KEYDOWN:
    {
        UINT virtualKeyCode = (UINT)wParam;
        RECT windowRect;
        int offset = 1;

        if (GetWindowRect(hWnd, &windowRect))
        {
            int currentX = windowRect.left;
            int currentY = windowRect.top;

            if (virtualKeyCode == VK_UP)
            {
                // Move window up
                MoveWindow(hWnd, currentX, currentY - offset, width, height, TRUE);
            }
            else if (virtualKeyCode == VK_DOWN)
            {
                // Move window down
                MoveWindow(hWnd, currentX, currentY + offset, width, height, TRUE);
            }
            else if (virtualKeyCode == VK_RIGHT)
            {
                // Move window right
                MoveWindow(hWnd, currentX + offset, currentY, width, height, TRUE);
            }
            else if (virtualKeyCode == VK_LEFT)
            {
                // Move window left
                MoveWindow(hWnd, currentX - offset, currentY, width, height, TRUE);
            }
        }

        break;
    }
    case WM_WINDOWPOSCHANGING:
    {
        WINDOWPOS* pWinPos = (WINDOWPOS*)lParam;
        pWinPos->x = max(parentClientRect.left + BORDER_EFFECT_SIZE, pWinPos->x);
        pWinPos->y = max(parentClientRect.top + WIN_BAR_SIZE, pWinPos->y);

        pWinPos->x = min(parentClientRect.right - width - BORDER_EFFECT_SIZE, pWinPos->x);
        pWinPos->y = min(parentClientRect.bottom - height - BORDER_EFFECT_SIZE, pWinPos->y);

        break;
    }
    case WM_CLOSE: {
        DestroyWindow(hWnd);
        return 0;
    }
    case WM_DESTROY: {
        // Cleanup: the bitmap we didn't delete gets deleted
        SetWindowLongPtr(hWnd, GWLP_USERDATA, 0);
        if (hbmSticker != NULL) {
            hbmSticker = NULL;
        }
        return 0;
    }
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}