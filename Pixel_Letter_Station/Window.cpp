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
			790, 5, 100, 20,
			hWnd, QuitButtonId, NULL, NULL);
		//Quit Button
		button = CreateWindowA("BUTTON",
			"Default",
			WS_VISIBLE | WS_CHILD | WS_BORDER | BS_OWNERDRAW,
			750, height - 80, 100, 20,
			hWnd, DefaultButtonId, NULL, NULL);
		//Editable TextBox
		letter = CreateWindowA("EDIT",
			"HELLO WORLD",
			WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE,
			centerW - 400, 60, 800, 450,
			hWnd, NULL, NULL, NULL);

		break;
	}
	case WM_DRAWITEM:
	{
		QuitButton(lParam);
		DefaultButton(lParam, L"Default");
		break;
	}
	case WM_PAINT: {

		WindowBar(hWnd, width);
		Title(hWnd, centerW);

		LONG_PTR style = GetWindowLongPtr(hWnd, GWL_STYLE); 
		style &= ~(WS_BORDER | WS_DLGFRAME | WS_CAPTION | WS_THICKFRAME); 
		SetWindowLongPtr(hWnd, GWL_STYLE, style);

		SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED); 

	}
	case WM_COMMAND: //Button logic
	{
		switch (LOWORD(wParam))
		{
		case 1: //Knows button number one was pressed
			PostQuitMessage(0);
			break;
		case 2: //Knows button number one was pressed
			MessageBeep(MB_ICONSTOP);
			break;
		}

		break;
	}
	case WM_NCHITTEST: // Window Dragging logic
	{
		// Convert the mouse position to screen coordinates
		POINT pt = { LOWORD(lParam), HIWORD(lParam) };
		ScreenToClient(hWnd, &pt);

		// Define the draggable area, e.g., top 50 pixels of the window
		RECT draggableArea = { 0, 0, width, WinBarSize }; // You need to define windowWidth

		// Check if the point is within the draggable area
		if (PtInRect(&draggableArea, pt)) {
			return HTCAPTION;
		}
		else {
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}
	case WM_CLOSE:
	{
		return DestroyWindow(hWnd);
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


