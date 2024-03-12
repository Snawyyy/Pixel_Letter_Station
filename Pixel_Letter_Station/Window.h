#pragma once

#include <Windows.h>
#include "CustomWindowUI.h"
#include "LetterWindow.h"
#include <locale>
#include <codecvt>
#include <vector>
#include <thread>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

extern SOCKET serverSock;
extern SOCKET clientSock;

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
