#pragma once

#include <Windows.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#include <objbase.h>

bool QuitButton(LPARAM lParam);
bool Title(HWND hWnd, int centerW);
bool DefaultButton(LPARAM lParam, const wchar_t* Text);
void WindowBar(HWND hWnd, int width);

#define QuitHMENU 1
#define DefaultHMENU 2
#define WinBarSize 30
