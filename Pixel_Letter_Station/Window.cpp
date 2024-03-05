#include "Window.h"

int width = 900;
int height = 600;
int centerW = width / 2;
int centerH = height / 2;
wchar_t wLetterText[LETTER_BOX_CAP] = {};
HBITMAP hBitmap;

SOCKET serverSock;
SOCKET clientSock;

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
				hWnd, (HMENU)SEND_BUTTON_ID, NULL, NULL);
			// Test
			HWND button = CreateWindowA("BUTTON",
				"Test",
				WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
				(width - LETTER_BOX_WIDTH - MARGIN), (height - (MARGIN * 2) - (BUTTON_HEIGHT / 2)), BUTTON_WIDTH * 2, BUTTON_HEIGHT,
				hWnd, (HMENU)6, NULL, NULL);
			// Initialize server
			HWND initializeServerButton = CreateWindowA("BUTTON",
				"Test",
				WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
				MARGIN * 2, MARGIN * 3, BUTTON_WIDTH, BUTTON_HEIGHT,
				hWnd, (HMENU)S_INITIALIZE_BUTTON_ID, NULL, NULL);
			// Connect to server
			HWND connectServerButton = CreateWindowA("BUTTON",
				"Test",
				WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
				MARGIN * 2, MARGIN * 5, BUTTON_WIDTH, BUTTON_HEIGHT,
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
			//Custimizable RichText edit box
			RichTextBoxPaint(letterContents);
			RichTextBoxPaint(letterTitle);

			break;
		}
		case WM_DRAWITEM:
		{
			QuitButton(lParam);
			MinimizeButton(lParam);
			DefaultButton(lParam, L"Send", SEND_BUTTON_ID);
			DefaultButton(lParam, L"Button 2", 6);
			DefaultButton(lParam, L"Initialize server", S_INITIALIZE_BUTTON_ID);
			DefaultButton(lParam, L"Connect to server", S_CONNECT_BUTTON_ID);

			break;
		}
		case WM_PAINT: 
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps); // Start painting


			// components
			WindowFrame(hdc, hWnd, width, height);
			WindowBar(hdc, hWnd, width);
			Title(hdc, hWnd, centerW);

			LetterBackground(hdc, hWnd,  width,  height);

			EndPaint(hWnd, &ps); // End painting
			break;
		}
		case WM_COMMAND: //Button logic
		{
			switch (LOWORD(wParam))
			{
			case 1: //Knows what button number was pressed
				PostQuitMessage(0);
				break;
			case 2:
				ShowWindow(hWnd, SW_MINIMIZE);
				break;
			case S_INITIALIZE_BUTTON_ID:
			{
				serverSock = InitializeServer();
				break;
			}
			case S_CONNECT_BUTTON_ID:
			{
				clientSock = ConnectToServer();
				break;
			}
			case SEND_BUTTON_ID:
			{
				GetWindowText(letterContents, &wLetterText[0], LETTER_BOX_CAP);

				// Convert wchar_t* string to char* string
				size_t size = wcslen(wLetterText) * MB_CUR_MAX + 1; // Determine buffer size
				size_t convertedChars = 0;

				vector<char> buffer(size);
				errno_t err = wcstombs_s(&convertedChars, buffer.data(), size, wLetterText, _TRUNCATE);

				if (err != 0) {
					std::cerr << "Error converting string." << std::endl;
					break;
				}

				std::cout << buffer.data() << std::endl; // Output the converted string

				cout << "Sending data to client. Size: " << buffer.size() << " bytes." << endl;
				int bytesSent = send(serverSock, buffer.data(), buffer.size(), 0);
				if (bytesSent == SOCKET_ERROR) {
					cout << "Failed to send data. Error code: " << WSAGetLastError() << endl;
				}
				else {
					cout << "Successfully sent " << bytesSent << " bytes." << endl;
				}				break;
			}
			case 6:
			{
				string data = RecvData(clientSock);

				size_t size = data.size() + 1; // Size for wide char array

				std::vector<wchar_t> wbuffer(size);
				size_t convertedChars = 0;

				// Convert char to wchar_t safely
				errno_t err = mbstowcs_s(&convertedChars, wbuffer.data(), size, data.c_str(), _TRUNCATE);

				if (err != 0) {
					std::cerr << "Error converting string." << std::endl;
					return 1;
				}

				std::wcout << wbuffer.data() << std::endl; // Output the converted string
				MessageBoxW(NULL, wbuffer.data(), L"OK", MB_OK);
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

	DWORD style = WS_POPUP;


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

