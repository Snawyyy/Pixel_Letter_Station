#pragma once
#include "Window.h"

HWND CreateUserWindow(HWND hParent, HINSTANCE hInstance, int x, int y, int width, int height, HBITMAP bitmapHandle);
LRESULT CALLBACK UserWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
