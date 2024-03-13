#pragma once
#include "Window.h"

HBITMAP GetLetter(HWND hWnd, int posX, int posY);

vector<BYTE> SerializeBitmap(HBITMAP hBitmap);
HBITMAP DeserializeBitmap(const vector<BYTE>& bitmapData);

void ReceiveLetterFromServer(SOCKET socket, HWND hWnd);

