#include "LetterWindow.h"

bool pressingPen = false;

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

    static HDC penHdc;

    // --UserDrawingSettings-- // 

    RECT drawingBorder; // Area able to draw in
    SetRect(&drawingBorder,
        rcClient.left + BORDER_EFFECT_SIZE + SMALL_MARGIN,
        rcClient.top + WIN_BAR_SIZE + SMALL_MARGIN,
        rcClient.left + BORDER_EFFECT_SIZE + SMALL_MARGIN + LETTER_BOX_BORDER_W,
        rcClient.top + WIN_BAR_SIZE + SMALL_MARGIN + LETTER_BOX_BORDER_H);

    penHdc = GetDC(hWnd);

    POINT cursorPos; // Pen position (calculated on LMouseButtonDown

    // pen settings
    static HPEN currentPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0)); // Default color
    static HPEN oldPen = (HPEN)SelectObject(penHdc, currentPen);


    // --Default Colors-- //

    COLORREF black = RGB(0, 0, 0);
    COLORREF white = RGB(255, 255, 255);
    COLORREF red = RGB(255, 0, 0);
    COLORREF yellow = RGB(255, 255, 0);
    COLORREF green = RGB(0, 255, 0);
    COLORREF blue = RGB(0, 0, 255);



    switch (uMsg)
    {
    case WM_CREATE: // where you create all the interface
    {
        // --Window Ui buttons-- // 
        // 
        // Send Button
        HWND sendButton = CreateWindowA("BUTTON",
            "Send",
            WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
            width - BORDER_EFFECT_SIZE - SMALL_MARGIN - BUTTON_WIDTH, (height - (MARGIN * 2) - (BUTTON_HEIGHT / 2)), BUTTON_WIDTH, BUTTON_HEIGHT,
            hWnd, (HMENU)SEND_ID, NULL, NULL);

        // color palate
        // black
        HWND black = CreateWindowA("BUTTON",
            "black",
            WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
            BORDER_EFFECT_SIZE + SMALL_MARGIN, (height - (MARGIN * 2) - (BUTTON_HEIGHT / 2)), BUTTON_HEIGHT, BUTTON_HEIGHT,
            hWnd, (HMENU)2, NULL, NULL);
        // white
        HWND white = CreateWindowA("BUTTON",
            "white",
            WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
            BORDER_EFFECT_SIZE + SMALL_MARGIN * 2 + BUTTON_HEIGHT, (height - (MARGIN * 2) - (BUTTON_HEIGHT / 2)), BUTTON_HEIGHT, BUTTON_HEIGHT,
            hWnd, (HMENU)3, NULL, NULL);
        // red
        HWND red = CreateWindowA("BUTTON",
            "red",
            WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
            BORDER_EFFECT_SIZE + SMALL_MARGIN * 3 + BUTTON_HEIGHT * 2, (height - (MARGIN * 2) - (BUTTON_HEIGHT / 2)), BUTTON_HEIGHT, BUTTON_HEIGHT,
            hWnd, (HMENU)4, NULL, NULL);
        // yellow
        HWND yellow = CreateWindowA("BUTTON",
            "yellow",
            WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
            BORDER_EFFECT_SIZE + SMALL_MARGIN * 4 + BUTTON_HEIGHT * 3, (height - (MARGIN * 2) - (BUTTON_HEIGHT / 2)), BUTTON_HEIGHT, BUTTON_HEIGHT,
            hWnd, (HMENU)5, NULL, NULL);
        // green
        HWND green = CreateWindowA("BUTTON",
            "green",
            WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
            BORDER_EFFECT_SIZE + SMALL_MARGIN * 5 + BUTTON_HEIGHT * 4, (height - (MARGIN * 2) - (BUTTON_HEIGHT / 2)), BUTTON_HEIGHT, BUTTON_HEIGHT,
            hWnd, (HMENU)6, NULL, NULL);
        // blue
        HWND blue = CreateWindowA("BUTTON",
            "blue",
            WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
            BORDER_EFFECT_SIZE + SMALL_MARGIN * 6 + BUTTON_HEIGHT * 5, (height - (MARGIN * 2) - (BUTTON_HEIGHT / 2)), BUTTON_HEIGHT, BUTTON_HEIGHT,
            hWnd, (HMENU)7, NULL, NULL);

        // --Window Bar Buttons-- //
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
            RECT bitmapRect;
            SetRect(&bitmapRect,
                rcClient.left + BORDER_EFFECT_SIZE + SMALL_MARGIN,
                rcClient.top + WIN_BAR_SIZE + SMALL_MARGIN,
                rcClient.left - BORDER_EFFECT_SIZE - SMALL_MARGIN,
                rcClient.bottom - (MARGIN * 5 + SMALL_MARGIN));

            HBITMAP hBitmap = GetLetter(hWnd, bitmapRect); // Retrieve the bitmap handle from GetLetter

            vector<BYTE> BitMap = SerializeBitmap(hBitmap);
            SendData(serverSock, BitMap);
            DestroyWindow(hWnd);
            break;
        }
        case 2:
        {
            // Changes pen to the desired color
            // Delete the old pen
            if (currentPen != NULL)
                DeleteObject(currentPen);

            currentPen = CreatePen(PS_SOLID, 1, black); // Red color
            break;
        }
        case 3:
        {
            // Changes pen to the desired color
            // Delete the old pen
            if (currentPen != NULL)
                DeleteObject(currentPen);
            currentPen = CreatePen(PS_SOLID, 1, white); // Red color
            break;
        }
        case 4:
        {
            // Changes pen to the desired color
            // Delete the old pen
            if (currentPen != NULL)
                DeleteObject(currentPen);
            currentPen = CreatePen(PS_SOLID, 1, red); // Red color
            break;
        }
        case 5:
        {
            // Changes pen to the desired color
            // Delete the old pen
            if (currentPen != NULL)
                DeleteObject(currentPen);
            currentPen = CreatePen(PS_SOLID, 1, yellow); // Red color
            break;
        }
        case 6:
        {
            // Changes pen to the desired color
            // Delete the old pen
            if (currentPen != NULL)
                DeleteObject(currentPen);
            currentPen = CreatePen(PS_SOLID, 1, green); // Red color
            break;
        }
        case 7:
        {
            // Changes pen to the desired color
            // Delete the old pen
            if (currentPen != NULL)
                DeleteObject(currentPen);
            currentPen = CreatePen(PS_SOLID, 1, blue); // Red color
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


        HGDIOBJ oldBitmap = SelectObject(hdcMem, hbmScreen); // Use the bitmap handle

        // Get bitmap dimensions
        BITMAP bitmap;
        GetObject(hbmScreen, sizeof(bitmap), &bitmap);

        RECT bitmapRect;
        SetRect(&bitmapRect,
            rcClient.left + BORDER_EFFECT_SIZE + SMALL_MARGIN,
            rcClient.top + WIN_BAR_SIZE + SMALL_MARGIN,
            rcClient.left - BORDER_EFFECT_SIZE - SMALL_MARGIN,
            rcClient.bottom - (MARGIN * 5 + SMALL_MARGIN));

        // Draw the bitmap
        BitBlt(hdc,
            bitmapRect.left, // left
            bitmapRect.top, // top
            LETTER_BOX_BORDER_W, // width
            LETTER_BOX_BORDER_H, // height
            hdcMem, 0, 0, SRCCOPY);

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

        ColorButton(lParam, 2, black);
        ColorButton(lParam, 3, white);
        ColorButton(lParam, 4, red);
        ColorButton(lParam, 5, yellow);
        ColorButton(lParam, 6, green);
        ColorButton(lParam, 7, blue);

        break;
    }
    case WM_LBUTTONDOWN:
    {
        // the drawing on letter logic
        pressingPen = true;
        oldPen = (HPEN)SelectObject(penHdc, currentPen);

        thread drawing(draw, cursorPos, hWnd, penHdc, drawingBorder);
        drawing.detach();
        break;
    }
    case WM_LBUTTONUP:
    {
        pressingPen = false;
        ReleaseDC(hWnd, penHdc); // release memory
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
        // Clean the brush
        if (currentPen != NULL)
            DeleteObject(currentPen);

        SendMessage(GetParent(hWnd), WM_LETTER_WINDOW, (WPARAM)101, 0);
        DestroyWindow(hWnd);
        return 0; 
    }
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void draw(POINT cursorPos, HWND hWnd, HDC penHdc, RECT border)
{
    // get Cursor pos to for starting point of line
    GetCursorPos(&cursorPos);
    ScreenToClient(hWnd, &cursorPos);

    // set prevCursorPos to current cursor position so line would start on clicked point
    POINT prevCursorPos = cursorPos;

    while (pressingPen) // if drawing
    {
        // get cursor pos
        GetCursorPos(&cursorPos);
        ScreenToClient(hWnd, &cursorPos);
        if (cursorPos.x >= border.left && cursorPos.x <= border.right && cursorPos.y >= border.top && cursorPos.y <= border.bottom)
        {
        MoveToEx(penHdc, prevCursorPos.x, prevCursorPos.y, NULL); // move start of line to the previous x,y cords captured
        LineTo(penHdc, cursorPos.x, cursorPos.y); // draw line from previous point to current one

        prevCursorPos = cursorPos;
        }
        else
        {
            prevCursorPos = cursorPos;
        }
    }
    return;
}