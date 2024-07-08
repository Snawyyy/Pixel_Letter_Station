#pragma once

#include <Windows.h>
#include "resource.h"
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#include <objbase.h>
#include <Richedit.h>
#pragma comment(lib, "comctl32.lib")
#include "WinServer.h"
#include "StickerManager.h"

LRESULT UserButton(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//void LetterBackground(HDC hdc, HWND hWnd);

void RichTextBoxPaint(HWND Box);

LRESULT StickerMenuButton(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void SetWindowTransparency(HWND hWnd);









