#pragma once
#include "CustomWindowUI.h"
#include <Windows.h>
#include "resource.h"
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#include <objbase.h>
#include <Richedit.h>
#pragma comment(lib, "comctl32.lib")
#include "WinServer.h"
#include "StickerManager.h"

class Ui
{
public:
	HWND hWnd;

	Ui(HWND hw) :hWnd(hw)
	{

	}

	void DrawBorder()
	{

	}

	COLORREF GetShadow(COLORREF color, float factor)
	{
		if (factor > 1.0)
		{
			factor = 1.0;
		}
		if (factor < 0.0)
		{
			factor = 0.0;
		}
		BYTE red = GetRValue(color);
		BYTE green = GetGValue(color);
		BYTE blue = GetBValue(color);
		int hueShift = 35;

		red = static_cast<BYTE>(red * factor);
		green = static_cast<BYTE>(green * factor);
		blue = static_cast<BYTE>(blue * factor);

		return RGB(red + hueShift, green, blue);
	}

	COLORREF GetShine(COLORREF color, float factor)
	{
		if (factor > 1.0)
		{
			factor = 1.0;
		}
		if (factor < 0.0)
		{
			factor = 0.0;
		}
		BYTE red = GetRValue(color);
		BYTE green = GetGValue(color);
		BYTE blue = GetBValue(color);
		int hueShift = 35;

		red = static_cast<BYTE>(red + (255 - red) * factor);
		green = static_cast<BYTE>(green + (255 - green) * factor);
		blue = static_cast<BYTE>(blue + (255 - blue) * factor);

		return RGB(red, green, blue - hueShift);
	}
};