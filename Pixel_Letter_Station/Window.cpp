#include "Window.h"

int width = 900;
int height = 600;
int centerW = width / 2;
int centerH = height / 2;
wchar_t wLetterText[LETTER_BOX_CAP] = {};
HBITMAP hBitmap;

SOCKET serverSock;
SOCKET clientSock;
int isConnected = 0;

HWND letterContents;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE: // where you create all the interface
		{

			// Window Bar Buttons
			// 
			// Quit Button
			HWND quitButton = CreateWindowA("BUTTON",
				"Quit",
				WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
				(width - BAR_BUTTON_SIZE - BAR_MARGIN), BAR_MARGIN, BAR_BUTTON_SIZE, BAR_BUTTON_SIZE,
				hWnd, (HMENU)QUIT_BUTTON_ID, NULL, NULL);
			// Minimize Button
			HWND minimizeButton = CreateWindowA("BUTTON",
				"-",
				WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
				(width - (BAR_BUTTON_SIZE * 2) - (BAR_MARGIN * 2)), BAR_MARGIN, BAR_BUTTON_SIZE, BAR_BUTTON_SIZE,
				hWnd, (HMENU)MINIMIZE_BUTTON_ID, NULL, NULL);

			// Window Ui buttons
			// 
			// Send Button
			HWND sendButton = CreateWindowA("BUTTON",
				"Send",
				WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
				width - MARGIN - BUTTON_WIDTH, (height - (MARGIN * 2) - (BUTTON_HEIGHT / 2)), BUTTON_WIDTH, BUTTON_HEIGHT,
				hWnd, (HMENU)INK_LETTER_BUTTON_ID, NULL, NULL);
			// Test
			HWND button = CreateWindowA("BUTTON",
				"Test",
				WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
				(width - LETTER_BOX_WIDTH - MARGIN), (height - (MARGIN * 2) - (BUTTON_HEIGHT / 2)), BUTTON_WIDTH * 2, BUTTON_HEIGHT,
				hWnd, (HMENU)6, NULL, NULL);
			// Test
			HWND Sticker = CreateWindowA("BUTTON",
				"Test",
				WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
				(MARGIN * 2), (height - (MARGIN * 2) - (BUTTON_HEIGHT / 2)), BUTTON_WIDTH, BUTTON_HEIGHT,
				hWnd, (HMENU)7, NULL, NULL);
			// Initialize server
			HWND initializeServerButton = CreateWindowA("BUTTON",
				"Test",
				WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
				MARGIN * 2, MARGIN * 5, BUTTON_WIDTH * 1.5, BUTTON_HEIGHT,
				hWnd, (HMENU)S_INITIALIZE_BUTTON_ID, NULL, NULL);
			// Connect to server
			HWND connectServerButton = CreateWindowA("BUTTON",
				"Test",
				WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
				MARGIN * 2, MARGIN * 7, BUTTON_WIDTH * 1.5, BUTTON_HEIGHT,
				hWnd, (HMENU)S_CONNECT_BUTTON_ID, NULL, NULL);

			// Letter UI
			// 
			// Letter Title
			HWND letterTitle = CreateWindowA("RichEdit20W",
				"-Title-",
				WS_VISIBLE | WS_CHILD | ES_CENTER,
				((width - (LETTER_BOX_WIDTH / 2) - MARGIN) - (LETTER_BOX_WIDTH / 2)), MARGIN * 4, LETTER_BOX_WIDTH, MARGIN,
				hWnd, NULL, NULL, NULL);
			// Letter Contents
			letterContents = CreateWindowA("RichEdit20W",
				"Write Here...",
				WS_VISIBLE | WS_CHILD | ES_MULTILINE,
				(width - LETTER_BOX_WIDTH - MARGIN), MARGIN * 6, LETTER_BOX_WIDTH, LETTER_BOX_HEIGHT,
				hWnd, NULL, NULL, NULL);
			// Customizable RichText edit box
			RichTextBoxPaint(letterContents);
			RichTextBoxPaint(letterTitle);

			SetTimer(hWnd, TIMER_UPDATE_ID, 1000, NULL);

			break;
		}
		case WM_TIMER:
		{
			if (wParam == TIMER_UPDATE_ID)
			{
				if (isConnected == 1) // only if connected try and receive data to not crash
				{

				}
			}
			break;
		}
		case WM_DRAWITEM:
		{
			QuitButton(lParam, QUIT_BUTTON_ID);
			MinimizeButton(lParam);
			DefaultButton(lParam, L"Ink Letter", INK_LETTER_BUTTON_ID);
			DefaultButton(lParam, L"Button 2", 6);
			DefaultButton(lParam, L"Sticker", 7);
			DefaultButton(lParam, L"Initialize server", S_INITIALIZE_BUTTON_ID);
			DefaultButton(lParam, L"Connect to server", S_CONNECT_BUTTON_ID);

			break;
		}
		case WM_PAINT: 
		{
			UpdateWindow(g_hwndSticker);
			InvalidateRect(g_hwndSticker, NULL, TRUE);

			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps); // Start painting


			// components
			WindowFrame(hdc, hWnd, width, height);
			WindowBar(hdc, hWnd, width);
			Title(hdc, hWnd, centerW);

			LetterBackground(hdc, hWnd,  width,  height);

			ServerStatusBar(hdc, isConnected);

			EndPaint(hWnd, &ps); // End painting

			break;
		}
		case WM_COMMAND: // Button logic
		{
			switch (LOWORD(wParam))
			{
			case QUIT_BUTTON_ID: // Knows what button number was pressed
				PostQuitMessage(0);
				break;
			case MINIMIZE_BUTTON_ID:
				ShowWindow(hWnd, SW_MINIMIZE);
				break;
			case S_INITIALIZE_BUTTON_ID:
			{
				if (serverSock == NULL)
				{
					serverSock = InitializeServer();
				}
				if (serverSock != NULL && isConnected != 1) // Checks if is running the server or connected to it.
				{
					isConnected = 2;
				}
				// Invalidate the status bar area
				RECT rect;
				GetClientRect(hWnd, &rect); // Assuming status bar is at the top of the window
				rect.bottom = rect.top + (MARGIN * 4); // Adjust height as needed
				InvalidateRect(hWnd, &rect, TRUE);

				// Redraw immediately
				UpdateWindow(hWnd);
				break;
			}
			case S_CONNECT_BUTTON_ID:
			{
				if (clientSock == NULL) 
				{
					clientSock = ConnectToServer();
				}
				if (clientSock != NULL && isConnected != 2) // Checks if is running the server or connected to it.
				{
					isConnected = 1;
				}
				// Invalidate the status bar area
				RECT rect;
				GetClientRect(hWnd, &rect); // Assuming status bar is at the top of the window
				rect.bottom = rect.top + (MARGIN * 4); // Adjust height as needed
				InvalidateRect(hWnd, &rect, TRUE);

				// Redraw immediately
				UpdateWindow(hWnd);
				break;
			}
			case INK_LETTER_BUTTON_ID:
			{
				int posX = width - LETTER_BOX_WIDTH - MARGIN - SMALL_MARGIN;
				int PosY = WIN_BAR_SIZE + MARGIN;
				HBITMAP hBitmap = GetLetter(hWnd, posX, PosY); // Retrieve the bitmap handle from GetLetter

				if (hBitmap != NULL) // Check if the bitmap handle is valid
				{
					HINSTANCE hInstance = GetModuleHandle(NULL);
					CreateLetterWindow(hWnd, hInstance, 100, 100, LETTER_BOX_WIDTH + (SMALL_MARGIN * 2) + (BAR_MARGIN * 2) - 1 + (SMALL_MARGIN * 2), height - (MARGIN * 5.5) + WIN_BAR_SIZE + BAR_MARGIN + (SMALL_MARGIN * 3) + MARGIN + BUTTON_HEIGHT, hBitmap);

				}
				else
				{
					MessageBox(NULL, L"Failed to retrieve bitmap from GetLetter\n", L"Fail", MB_OK);
				}

				break;
			}
			case 6:
			{
				thread recMessage(ReceiveLetterFromServer, clientSock, hWnd);
				recMessage.detach();
				break;
			}
			case 7:
			{
				HINSTANCE hInstance = GetModuleHandle(NULL);
				CreateSticker(hWnd, hInstance, 0, 0, 25);
				break;
			}
			}
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

Window::Window(): m_hinstance(GetModuleHandle(nullptr))
{

	const wchar_t* CLASS_NAME = L"Snawy's Window Class";

	WNDCLASS wndClass = {};
	wndClass.lpszClassName = CLASS_NAME;
	wndClass.hInstance = m_hinstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.lpfnWndProc = WindowProc;

	wndClass.hbrBackground = CreateSolidBrush(RGB(255, 250, 215));
	RegisterClass(&wndClass);

	DWORD style = WS_POPUP | WS_CLIPCHILDREN;

	WNDCLASS wc = {};
	wc.lpfnWndProc = LetterWindowProc;
	wc.hInstance = m_hinstance;
	wc.lpszClassName = L"ChildWindowClass";

	RegisterClass(&wc);


	WNDCLASS Sc = {};
	Sc.lpfnWndProc = StickerWindowProc;
	Sc.hInstance = m_hinstance;
	Sc.lpszClassName = L"StickerWindowClass";

	RegisterClass(&Sc);


	m_hwnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"Pixel Letter Station",
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		m_hinstance,
		NULL
	);

	ShowWindow(m_hwnd, SW_SHOW);

}

Window::~Window()
{
	const wchar_t* CLASS_NAME = L"Snawy's Window Class";

	UnregisterClass(CLASS_NAME, m_hinstance);
}

bool Window::ProcessMessages()
{
	MSG msg = {};

	while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return false;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}
	return true;
}

