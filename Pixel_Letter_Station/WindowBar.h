#pragma once
#include "Ui.h"

class WindowBar:Ui
{
public:
	int width;
	HDC hdc;

	WindowBar(HDC hd, HWND hWnd) :Ui(hWnd), hdc(hd)
	{
		width = GetWidth(hWnd);
	}

	void Draw(bool title)
	{
		DrawWindowBar();
		if (title)
		{
			DrawTitle();
		}
	}

	void DrawWindowBar()
	{
		// Set the color for the rectangle (optional)
		HBRUSH brush = CreateSolidBrush(WINODW_UI_COLOR); 
		HPEN nullPen = CreatePen(PS_NULL, 1, RGB(0, 0, 0)); // Null pen, color doesn't matter
		SelectObject(hdc, brush);
		SelectObject(hdc, nullPen);

		// Draw the rectangle
		// Parameters: HDC, left, top, right, bottom
		Rectangle(hdc, 0, 0, width, WIN_BAR_SIZE);

		// Draw the Border Shadow
		brush = CreateSolidBrush(GetShadow(WINODW_UI_COLOR, factor));
		SelectObject(hdc, brush);
		Rectangle(hdc, 0, WIN_BAR_SIZE, width, WIN_BAR_SIZE - BORDER_EFFECT_SIZE);
		Rectangle(hdc, width - BORDER_EFFECT_SIZE + 1, 0, width + 1, WIN_BAR_SIZE);

		// Draw the Border shine
		brush = CreateSolidBrush(GetShine(WINODW_UI_COLOR, factor));
		SelectObject(hdc, brush);
		Rectangle(hdc, 0, 0, width + 1, BORDER_EFFECT_SIZE);
		Rectangle(hdc, 0, 0, BORDER_EFFECT_SIZE, WIN_BAR_SIZE);



		// Clean up
		DeleteObject(brush);
		DeleteObject(nullPen);
	}

	void DrawTitle()
	{
		HBITMAP hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_LOGO), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
		if (hBitmap == NULL)
		{
			MessageBox(NULL, L"Load Failed", L"Fail", MB_OK);
		}
		HDC hdcMem = CreateCompatibleDC(hdc);
		HGDIOBJ oldBitmap = SelectObject(hdcMem, hBitmap);


		BITMAP bitmap;
		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
		int height = WIN_BAR_SIZE - (BORDER_EFFECT_SIZE * 3);
		int width = (bitmap.bmWidth * height) / bitmap.bmHeight;
		StretchBlt(hdc, BORDER_EFFECT_SIZE * 2, (WIN_BAR_SIZE / 2) - (height / 2), width, height, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		// Custom drawing code goes here
		HFONT hFont = TitleFont();
		HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

		SetTextColor(hdc, PAPER_COLOR);// text color
		SetBkMode(hdc, TRANSPARENT); // To make background transparent
		TextOut(hdc, SMALL_MARGIN + BORDER_EFFECT_SIZE * 2 + width, ((WIN_BAR_SIZE / 2) - (TITLE_SIZE / 2) + 1), L"Pixel Letter Station", strlen("Pixel Letter Station"));
	}

	HFONT TitleFont()
	{
		HFONT hFont = CreateFont(
			TITLE_SIZE,               // Height of the font
			0,                     // Average character width (0 lets the system choose the best value)
			0,                     // Angle of escapement
			0,                     // Base-line orientation angle
			FW_BOLD,               // Font weight (FW_BOLD for bold)
			FALSE,                 // Italic attribute option
			FALSE,                 // Underline attribute option
			FALSE,                 // Strikeout attribute option
			ANSI_CHARSET,          // Character set identifier
			OUT_DEFAULT_PRECIS,    // Output precision
			CLIP_DEFAULT_PRECIS,   // Clipping precision
			NONANTIALIASED_QUALITY,       // Output quality
			DEFAULT_PITCH | FF_SWISS, // Pitch and family
			L"Arial");              // Font name
		return hFont;
	}
};