#pragma once

#include <Windows.h>
#include "CustomWindowUI.h"
#include <Richedit.h>
#pragma comment(lib, "comctl32.lib")


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
