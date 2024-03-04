#pragma once

#include <Windows.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#include <objbase.h>

bool QuitButton(LPARAM lParam);
bool MinimizeButton(LPARAM lParam);
bool DefaultButton(LPARAM lParam, const wchar_t* Text, int buttonId);
bool Title(HDC hdc, HWND hWnd, int centerW);
void WindowBar(HDC hdc, HWND hWnd, int width);
void WindowFrame(HDC hdc, HWND hWnd, int width, int height);

 // HMENU id
#define TITLE_ID 0
#define QUIT_BUTTON_ID 1
#define MINIMIZE_BUTTON_ID 2
#define DEFAULT_BUTTON_ID 3
#define INVISBLE_TEXTBOX_SUBCLASS_ID 101
// learn about enum

 //Window Bar Settings
#define TITLE_SIZE 20
#define WIN_BAR_SIZE 30
#define BAR_MARGIN  5
#define BAR_BUTTON_SIZE  20
#define BORDER_EFFECT_SIZE 4

 //Ui Settings
#define MARGIN  20

#define LTEXT_BOX_WIDTH 700 //Letter writing box
#define LTEXT_BOX_HEIGHT 450 

#define BUTTON_WIDTH 100 //Button
#define BUTTON_HEIGHT 20

