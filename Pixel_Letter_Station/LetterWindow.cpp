#include "LetterWindow.h"


HWND CreateLetterWindow(HWND hParent, HINSTANCE hInstance, int x, int y, int width, int height, HBITMAP bitmapHandle)
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
    HWND hwndLetter = CreateWindowEx(
        0,                 // Optional window styles.
        CLASS_NAME,        // Window class
        L"Child Window",   // Window text
        WS_VISIBLE | WS_POPUP | WS_CLIPCHILDREN, // Window style
        x, y, width, height,   // Size and position
        hParent,           // Parent window    
        NULL,              // Menu
        hInstance,         // Instance handle
        (LPVOID)bitmapHandle   // Additional application data
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
            hWnd, (HMENU)SEND_ID, NULL, NULL);
        // Test
        HWND Sticker = CreateWindowA("BUTTON",
            "Test",
            WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
            (MARGIN * 2), (height - (MARGIN * 2) - (BUTTON_HEIGHT / 2)), BUTTON_WIDTH, BUTTON_HEIGHT,
            hWnd, (HMENU)7, NULL, NULL);

        // Window Bar Buttons
        // 
        // Quit Button
        HWND quitButton = CreateWindowA("BUTTON",
            "Quit",
            WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
            (width - BAR_BUTTON_SIZE - BAR_MARGIN), BAR_MARGIN, BAR_BUTTON_SIZE, BAR_BUTTON_SIZE,
            hWnd, (HMENU)QUIT_BUTTON_ID, NULL, NULL);

        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        hbmScreen = reinterpret_cast<HBITMAP>(pCreate->lpCreateParams); // Retrieve and store the bitmap handle
    }
    case WM_COMMAND: // Button logic
    {

        switch (LOWORD(wParam))
        {

        case QUIT_BUTTON_ID: // Knows what button number was pressed
        {
            DestroyWindow(hWnd);

            break;
        }
        case SEND_ID:
        {
            int posX = BAR_MARGIN + SMALL_MARGIN;
            int PosY = WIN_BAR_SIZE + SMALL_MARGIN;
            HBITMAP hBitmap = GetLetter(hWnd, posX, PosY); // Retrieve the bitmap handle from GetLetter

            vector<BYTE> BitMap = SerializeBitmap(hBitmap);
            SendData(serverSock, BitMap);
            DestroyWindow(hWnd);
            break;
        }
        case 7:
        {
            HINSTANCE hInstance = GetModuleHandle(NULL);
            CreateSticker(hWnd, hInstance, 0, 0, 25);
            break;
        }
        }
        break;
    }
    case WM_PAINT:
    {
        if (g_hwndSticker != NULL)
        {
        UpdateWindow(g_hwndSticker);
        InvalidateRect(g_hwndSticker, NULL, TRUE);
        }
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        HDC hdcMem = CreateCompatibleDC(hdc);


        HGDIOBJ oldBitmap = SelectObject(hdcMem, hbmScreen); // Use the bitmap handle

        // Get bitmap dimensions
        BITMAP bitmap;
        GetObject(hbmScreen, sizeof(bitmap), &bitmap);

        // Draw the bitmap
        BitBlt(hdc, BAR_MARGIN + SMALL_MARGIN, WIN_BAR_SIZE + SMALL_MARGIN, LETTER_BOX_WIDTH + (SMALL_MARGIN * 2) - 2, height - (MARGIN * 5 + SMALL_MARGIN), hdcMem, 0, 0, SRCCOPY);
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
        QuitButton(lParam, QUIT_BUTTON_ID);
        DefaultButton(lParam, L"Send", SEND_ID);
        DefaultButton(lParam, L"Sticker", 7);
        break;
    }
    case WM_ERASEBKGND:
    {
        HDC hdc = (HDC)wParam;
        RECT rect;
        GetClientRect(hWnd, &rect);
        FillRect(hdc, &rect, CreateSolidBrush(BACKGROUND_COLOR)); // Fill with red
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
        // Cleanup: the bitmap we didn't delete gets deleted
        if (hbmScreen != NULL) {
            DeleteObject(hbmScreen); 
            hbmScreen = NULL;
        }
        DestroyWindow(hWnd);
        return 0; 
    }
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}