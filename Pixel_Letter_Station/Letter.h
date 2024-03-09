#pragma once

#include <Windows.h>

using namespace std;

HBITMAP GetLetter(HWND hWnd);

HWND CreateLetterWindow(HWND hParent, HINSTANCE hInstance, int x, int y, int width, int height);

LRESULT LetterWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
