#pragma once
#include "Window.h"

HBITMAP GetLetter(HWND hWnd);
vector<BYTE> SerializeBitmap(HBITMAP hBitmap);
HBITMAP DeserializeBitmap(const vector<BYTE>& bitmapData);

