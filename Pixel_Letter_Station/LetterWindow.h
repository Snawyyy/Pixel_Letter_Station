#pragma once

#include <Windows.h>
#include "Window.h"
#include "CustomWindowUI.h"
#include "LetterManager.h"
#include <thread>

using namespace std;


HWND CreateLetterWindow(HWND hParent, HINSTANCE hInstance, int x, int y, int width, int height, HBITMAP bitmapHandle);
LRESULT LetterWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#define WM_LETTER_WINDOW WM_USER + 100
