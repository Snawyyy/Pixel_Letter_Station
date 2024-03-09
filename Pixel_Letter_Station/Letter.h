#pragma once

#include <Windows.h>

using namespace std;

HBITMAP GetLetter(HWND hWnd);

HWND CreateChildWindow(HWND hParent, HINSTANCE hInstance, int x, int y, int width, int height);

LRESULT ChildWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
