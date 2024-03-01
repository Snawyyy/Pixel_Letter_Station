#include "Window.h"

HWND textField;
HWND button;
HWND letter;
int width = 900;
int height = 600;
int centerW = width / 2;
int centerH = height / 2;
int margin = 20;


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE: //where you create all the interface
	{
		//Quit Button
		button = CreateWindowA("BUTTON",
			"Quit",
			WS_VISIBLE | WS_CHILD | WS_BORDER | BS_OWNERDRAW,
			750, 20, 100, 20,
			hWnd, QuitButtonId, NULL, NULL);
		//Editable TextBox
		letter = CreateWindowA("EDIT",
			"HELLO WORLD",
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE,
			centerW - 400, 60, 800, 450,
			hWnd, NULL, NULL, NULL);

		break;
	}
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// Custom drawing code goes here
		HFONT hFont = CreateFont(
			20,               // Height of the font
			0,                     // Average character width (0 lets the system choose the best value)
			0,                     // Angle of escapement
			0,                     // Base-line orientation angle
			FW_EXTRABOLD,               // Font weight (FW_BOLD for bold)
			FALSE,                 // Italic attribute option
			FALSE,                 // Underline attribute option
			FALSE,                 // Strikeout attribute option
			ANSI_CHARSET,          // Character set identifier
			OUT_DEFAULT_PRECIS,    // Output precision
			CLIP_DEFAULT_PRECIS,   // Clipping precision
			DEFAULT_QUALITY,       // Output quality
			DEFAULT_PITCH | FF_SWISS, // Pitch and family
			L"Arial");              // Font name
		HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

		SetTextColor(hdc, RGB(0, 0, 0));// text color
		SetBkMode(hdc, TRANSPARENT); // To make background transparent
		TextOut(hdc, centerW - 70, 20, L"Pixel Letter Station", strlen("Pixel Letter Station"));
		EndPaint(hWnd, &ps);
		return 0; // Indicate we handled the message
	}
	case WM_COMMAND: //Button logic
	{
		switch (LOWORD(wParam))
		{
		case 1: //Knows button number one was pressed
			PostQuitMessage(0);
			break;
		}
		break;
	}
	case WM_DRAWITEM:
	{
		QuitButton(lParam);
		break;
	}
	case WM_CLOSE:
	{
		DestroyWindow(hWnd);
		break;
	}
	case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

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

	DWORD style = WS_BORDER;


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


