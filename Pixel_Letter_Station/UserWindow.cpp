#include "UserWindow.h"

HWND CreateUserWindow(HWND hParent, HINSTANCE hInstance, int x, int y, int width, int height)
{
    // Define the class name. Make sure this class is registered in WinMain.
    const wchar_t CLASS_NAME[] = L"UserWindowClass";

    // Get the dimensions of the parent window
    RECT parentRect;
    GetWindowRect(hParent, &parentRect);

    // Calculate the desired position and size for the child window
    // For example, to place it 50 pixels to the right and 50 pixels down from the parent's top-left corner
    x = (parentRect.right / 2) - (width / 2);
    y = (parentRect.bottom / 2) - (height / 2);


    // Create the window.
    HWND hwndUser = CreateWindowEx(
        0,                 // Optional window styles.
        CLASS_NAME,        // Window class
        L"Child Window",   // Window text
        WS_VISIBLE | WS_POPUP | WS_CLIPCHILDREN, // Window style
        x, y, width, height,   // Size and position
        hParent,           // Parent window    
        NULL,              // Menu
        hInstance,         // Instance handle
        NULL   // Additional application data
    );

    return hwndUser;
}

LRESULT CALLBACK UserWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    RECT rcClient;
    GetClientRect(hWnd, &rcClient);

    int width = rcClient.right - rcClient.left;
    int height = rcClient.bottom - rcClient.top;

    static int isConnected = 0;

    switch (uMsg)
    {
    case WM_CREATE: // where you create all the interface
    {
        // Quit Button
        HWND quitButton = CreateWindowA("BUTTON",
            "Quit",
            WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
            (width - BAR_BUTTON_SIZE - BAR_MARGIN), BAR_MARGIN, BAR_BUTTON_SIZE, BAR_BUTTON_SIZE,
            hWnd, (HMENU)QUIT_BUTTON_ID, NULL, NULL);
        // Initialize server
        HWND initializeServerButton = CreateWindowA("BUTTON",
            "Test",
            WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
            (width / 2) - (BUTTON_WIDTH * 1.5) / 2, height - BUTTON_HEIGHT - MARGIN, BUTTON_WIDTH * 1.5, BUTTON_HEIGHT,
            hWnd, (HMENU)S_INITIALIZE_BUTTON_ID, NULL, NULL);
        // Connect to server
        HWND connectServerButton = CreateWindowA("BUTTON",
            "Test",
            WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
            (width / 2) - (BUTTON_WIDTH * 1.5) / 2, height - (BUTTON_HEIGHT * 2) - (MARGIN * 2), BUTTON_WIDTH * 1.5, BUTTON_HEIGHT,
            hWnd, (HMENU)S_CONNECT_BUTTON_ID, NULL, NULL);
        break;
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
        case S_INITIALIZE_BUTTON_ID:
        {
            SendMessage(GetParent(hWnd), WM_USER_WINDOW, (WPARAM)S_INITIALIZE_BUTTON_ID, 0);
            break;
        }
        case S_CONNECT_BUTTON_ID:
        {
            SendMessage(GetParent(hWnd), WM_USER_WINDOW, (WPARAM)S_CONNECT_BUTTON_ID, 0);
            break;
        }
        }

        break;
    }
    case WM_MAIN_WINDOW:
    {
        int recConnected = (int)wParam;
        if ((isConnected != recConnected))
        {
            isConnected = recConnected;
            // Invalidate the status bar area
            RECT rect;
            GetClientRect(hWnd, &rect);
            InvalidateRect(hWnd, &rect, TRUE);

            // Redraw immediately
            UpdateWindow(hWnd);
        }
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // Bar and frame
        Ui frame(hWnd);
        frame.DrawFrame(hdc);

        WindowBar bar(hdc, hWnd);
        bar.Draw(false);

        ServerStatusBar statusBar(hWnd, hdc);
        statusBar.Draw(isConnected, (width / 2) - ((MARGIN * 8.5) / 2), MARGIN * 2);

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DRAWITEM:
    {
        Button quitButton(lParam, QUIT_BUTTON_ID, L"X");
        quitButton.Draw(RGB(255, 0, 0), RGB(0, 0, 0));

        Button serverButton(lParam, S_INITIALIZE_BUTTON_ID, L"Initialize server");
        serverButton.Draw(DEFULT_BUTTON_COLOR, RGB(0, 0, 0));

        Button ConnectButton(lParam, S_CONNECT_BUTTON_ID, L"Connect to server");
        ConnectButton.Draw(DEFULT_BUTTON_COLOR, RGB(0, 0, 0));
        break;
    }
    case WM_ERASEBKGND:
    {
        HDC hdc = (HDC)wParam;
        RECT rect;
        GetClientRect(hWnd, &rect);
        FillRect(hdc, &rect, CreateSolidBrush(BACKGROUND_COLOR));
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
    case WM_CLOSE: 
    {
        DestroyWindow(hWnd);
        return 0;
    }
    case WM_DESTROY:
    {
        SendMessage(GetParent(hWnd), WM_LETTER_WINDOW, (WPARAM)101, 0);
        DestroyWindow(hWnd);
        return 0;
    }
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}