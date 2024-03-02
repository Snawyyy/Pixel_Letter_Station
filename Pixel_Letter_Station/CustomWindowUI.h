#pragma once

#include <Windows.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#include <objbase.h>

bool QuitButton(LPARAM lParam);
bool MinimizeButton(LPARAM lParam);
bool Title(HWND hWnd, int centerW);
bool DefaultButton(LPARAM lParam, const wchar_t* Text);
void WindowBar(HWND hWnd, int width);

 // HMENU id
#define QuitHMENU 1
#define MinimizeHMENU 2
#define DefaultHMENU 3

 //Window Bar Settings
#define WinBarSize 30
#define BarMargin  5
#define BarButtonSize  20

 //Ui Settings

#define margin  20

#define LTextBoxWidth 800 //Letter writing box
#define LTextBoxHeight 500 

#define ButtonWidth 100 //Button
#define ButtonHeight 20

