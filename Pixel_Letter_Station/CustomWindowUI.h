#pragma once

#include <Windows.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#include <objbase.h>
#include <Richedit.h>
#pragma comment(lib, "comctl32.lib")
#include "WinServer.h"

bool QuitButton(LPARAM lParam, int buttonId);
bool MinimizeButton(LPARAM lParam);
bool DefaultButton(LPARAM lParam, const wchar_t* Text, int buttonId);
bool Title(HDC hdc, HWND hWnd, int centerW);
void WindowBar(HDC hdc, HWND hWnd, int width);
void WindowFrame(HDC hdc, HWND hWnd, int width, int height);

void LetterBackground(HDC hdc, HWND hWnd, int width, int height);

void RichTextBoxPaint(HWND Box);

void ServerStatusBar(HDC hdc, int isConnected);

 // HMENU id
#define TITLE_ID 0
#define QUIT_BUTTON_ID 1
#define MINIMIZE_BUTTON_ID 2
#define SEND_BUTTON_ID 3
#define S_INITIALIZE_BUTTON_ID 4
#define S_CONNECT_BUTTON_ID 5
#define INVISBLE_TEXTBOX_SUBCLASS_ID 101
#define TIMER_UPDATE_ID 1
// learn about enum

 //Window Bar Settings
#define TITLE_SIZE 20
#define WIN_BAR_SIZE 30
#define BAR_MARGIN  5
#define BAR_BUTTON_SIZE  20
#define BORDER_EFFECT_SIZE 4

 //Ui Settings
#define MARGIN  20
#define SMALL_MARGIN  7.5

#define LETTER_BOX_WIDTH 650 //Letter writing box
#define LETTER_BOX_HEIGHT 400 
#define LETTER_BOX_CAP 1400 // Max letters in the letter box

#define BUTTON_WIDTH 100 //Button
#define BUTTON_HEIGHT 30

