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

    BitBlt(hdcMemDC, 0, 0, LETTER_BOX_WIDTH + (SMALL_MARGIN * 2) - 2, height - (MARGIN * 2.5), hdcWindow, width - LETTER_BOX_WIDTH - MARGIN - SMALL_MARGIN, WIN_BAR_SIZE + MARGIN, SRCCOPY);

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
    static HBITMAP hbmScreen = NULL;

    switch (uMsg)
    {
    case WM_CREATE: // where you create all the interface
    {
        // Window Ui buttons
        // 
        // Send Button
        HWND sendButton = CreateWindowA("BUTTON",
            "Send",
            WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
            width - MARGIN - BUTTON_WIDTH, (height - (MARGIN * 2) - (BUTTON_HEIGHT / 2)), BUTTON_WIDTH, BUTTON_HEIGHT,
            hWnd, (HMENU)SEND_BUTTON_ID, NULL, NULL);
        // Window Bar Buttons
        // 
        // Quit Button
        HWND quitButton = CreateWindowA("BUTTON",
            "Quit",
            WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
            (width - BAR_BUTTON_SIZE - BAR_MARGIN), BAR_MARGIN, BAR_BUTTON_SIZE, BAR_BUTTON_SIZE,
            hWnd, (HMENU)8, NULL, NULL);

    }
    case WM_COMMAND: // Button logic
    {
        switch (LOWORD(wParam))
        {
        case 8: // Knows what button number was pressed
        {
            DestroyWindow(hWnd);
            break;
        }
        }
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        HDC hdcMem = CreateCompatibleDC(hdc);


        hbmScreen = GetLetter(GetParent(hWnd));
        HGDIOBJ oldBitmap = SelectObject(hdcMem, hbmScreen); // Use the bitmap handle

        // Get bitmap dimensions
        BITMAP bitmap;
        GetObject(hbmScreen, sizeof(bitmap), &bitmap);

        // Draw the bitmap
        BitBlt(hdc, BAR_MARGIN + SMALL_MARGIN, WIN_BAR_SIZE - 1 + SMALL_MARGIN, LETTER_BOX_WIDTH + (SMALL_MARGIN * 2) - 2, height - (MARGIN * 5 + SMALL_MARGIN), hdcMem, 0, 0, SRCCOPY);
        WindowFrame(hdc, hWnd, width, height);
        WindowBar(hdc, hWnd, width);

        // Cleanup
        SelectObject(hdcMem, oldBitmap);
        DeleteDC(hdcMem);

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DRAWITEM:
    { 
        QuitButton(lParam, 8);
        DefaultButton(lParam, L"Send", SEND_BUTTON_ID);
        break;
    }
    case WM_ERASEBKGND:
    {
        HDC hdc = (HDC)wParam;
        RECT rect;
        GetClientRect(hWnd, &rect);
        FillRect(hdc, &rect, CreateSolidBrush(RGB(255, 250, 215))); // Fill with red
        return TRUE; // Return non-zero value when processed
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
    case WM_CLOSE: {
        DestroyWindow(hWnd);
        return 0;  
    }
    case WM_DESTROY: {
        // Cleanup: the bitmap we didnt delete gets deleted
        if (hbmScreen != NULL) {
            DeleteObject(hbmScreen); 
            hbmScreen = NULL;
        }
        return 0; 
    }
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}