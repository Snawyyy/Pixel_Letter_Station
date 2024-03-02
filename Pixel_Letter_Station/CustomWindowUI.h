#pragma once

#include <Windows.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#include <objbase.h>

bool QuitButton(LPARAM lParam);
bool MinimizeButton(LPARAM lParam);
bool DefaultButton(LPARAM lParam, const wchar_t* Text);
bool Title(HDC hdc, HWND hWnd, int centerW);
void WindowBar(HDC hdc, HWND hWnd, int width);
void WindowFrame(HDC hdc, HWND hWnd, int width, int height);

 // HMENU id
#define QuitHMENU 1
#define MinimizeHMENU 2
#define DefaultHMENU 3
// learn about enum

 //Window Bar Settings
#define TilteSize 20
#define WinBarSize 30
#define BarMargin  5
#define BarButtonSize  20
#define BorderEffectSize 4

 //Ui Settings
#define margin  20

#define LTextBoxWidth 800 //Letter writing box
#define LTextBoxHeight 500 

#define ButtonWidth 100 //Button
#define ButtonHeight 20

