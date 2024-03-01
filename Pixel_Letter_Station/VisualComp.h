#pragma once

#include <Windows.h>

bool QuitButton(LPARAM lParam);
bool Title(HWND hWnd, int centerW);
bool DefaultButton(LPARAM lParam, const wchar_t* Text);

#define QuitHMENU 1
#define DefaultHMENU 2
