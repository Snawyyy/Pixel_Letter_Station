#pragma once
#include <Windows.h>
#include "CustomWindowUI.h"

using namespace std;

HWND CreateSticker(HWND hParent, HINSTANCE hInstance, int x, int y, int height);
LRESULT CALLBACK StickerWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

extern HWND g_hwndSticker;