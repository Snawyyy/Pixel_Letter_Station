#pragma once

#include <Windows.h>
#include "Window.h"
#include "LetterManager.h"
#include <thread>
#include "UiElements.h"

using namespace std;


HWND CreateLetterWindow(HWND hParent, HINSTANCE hInstance, int x, int y, int width, int height, HBITMAP bitmapHandle);
LRESULT LetterWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void draw(POINT cursorPos, HWND hWnd); // the drawing on window funcion

#define WM_LETTER_WINDOW WM_USER + 100
#define WM_LETTER_RECIVED WM_USER + 101
#define WM_DRAW_LINE WM_USER + 2
