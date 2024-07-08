#pragma once
#include "Ui.h"

class ServerStatusBar :Ui
{
public:
	HDC hdc;

	ServerStatusBar(HWND hWnd, HDC dc):Ui(hWnd), hdc(dc)
	{

	}

	void Draw(bool isConnected, int x, int y)
	{
		StatusBar(isConnected, x, y);
	}

	void StatusBar(bool isConnected, int x, int y)
	{
		int height = (MARGIN * 1.5) + SMALL_MARGIN;
		int width = MARGIN * 8.5;

		// First, draw the larger rectangle with a solid color
		HBRUSH brushMain = CreateSolidBrush(UI_BORDER); // Black color for the Border
		RECT rectMain = { x, y, x + width, y + height }; // Main rectangle coordinates
		FillRect(hdc, &rectMain, brushMain);

		//Then, the "Shine" by drawing it with the Shine color
		HBRUSH brushShading = CreateSolidBrush(GetShine(WINODW_UI_COLOR, factor)); // Brush for the cutout, using the Shine color
		RECT rectShading = { x + BORDER_EFFECT_SIZE, y + BORDER_EFFECT_SIZE, x + width - BORDER_EFFECT_SIZE, y + height - BORDER_EFFECT_SIZE }; // Smaller rectangle coordinates for the cutout
		FillRect(hdc, &rectShading, brushShading);

		//Then, the "Background" by drawing it with the paper color
		HBRUSH brushPaper = CreateSolidBrush(WINODW_UI_COLOR); // Brush for the cutout, using the window background color
		RECT rectCutout = { x + (BORDER_EFFECT_SIZE * 2), y + (BORDER_EFFECT_SIZE * 2), x + width - BORDER_EFFECT_SIZE, y + height - BORDER_EFFECT_SIZE }; // Smaller rectangle coordinates for the cutout
		FillRect(hdc, &rectCutout, brushPaper);

		StatusText(isConnected, x, y, height);

		// Clean up
		DeleteObject(brushMain);
		DeleteObject(brushShading);
		DeleteObject(brushPaper);
	}

	void StatusText(bool isConnected, int x, int y, int height)
	{
		// Custom text code goes here
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
		HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkMode(hdc, TRANSPARENT);

		TextOut(hdc, x + SMALL_MARGIN + BORDER_EFFECT_SIZE, y + (height / 2) + BORDER_EFFECT_SIZE - (TITLE_SIZE / 2), L"Status:", strlen("Status:"));
		if (isConnected == 0)
		{
			SetTextColor(hdc, STATUS_OFFLINE_COLOR);// text color
			TextOut(hdc, x + MARGIN * 3, y + (height / 2) + BORDER_EFFECT_SIZE - (TITLE_SIZE / 2), L"Offline", strlen("Offline"));
		}
		if (isConnected == 1)
		{
			SetTextColor(hdc, STATUS_ONLINE_COLOR);// text color
			TextOut(hdc, x + MARGIN * 3, y + (height / 2) + BORDER_EFFECT_SIZE - (TITLE_SIZE / 2), L"Connected", strlen("Connected"));
		}
		if (isConnected == 2)
		{
			SetTextColor(hdc, STATUS_Server_COLOR);// text color
			TextOut(hdc, x + MARGIN * 3, y + (height / 2) + BORDER_EFFECT_SIZE - (TITLE_SIZE / 2), L"server", strlen("server"));
		}
	}
};