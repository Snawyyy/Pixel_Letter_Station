#pragma once

#include <Windows.h>
#include "CustomWindowUI.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{
public:
	Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	~Window();

	bool ProcessMessages();

private:
	HINSTANCE m_hinstance;
	HWND m_hwnd;
};

#define TitleId (HMENU)0
#define QuitButtonId (HMENU)1
#define MinimizeButtonId (HMENU)2
#define DefaultButtonId (HMENU)3
