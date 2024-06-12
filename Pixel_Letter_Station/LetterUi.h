#pragma once
#include "Ui.h"

class LetterUi:Ui
{
public:
	HDC hdc;

	LetterUi(HDC hd, HWND hWnd) :Ui(hWnd), hdc(hd)
	{

	}

	void Draw(RECT rectMain)
	{
		RECT clientRect = ScreenToClientRect(hWnd, rectMain);
		LetterBackground(hdc, hWnd, clientRect);
	}

	void LetterBackground(HDC hdc, HWND hWnd, RECT rectMain)
	{
		// First, draw the border, a larger rectangle with a solid color
		HBRUSH brushMain = CreateSolidBrush(LETTER_BORDER); // Black color for the Border

		FillRect(hdc, &rectMain, brushMain);

		//Then, the "Shadow" by drawing it with the paper color
		HBRUSH brushShading = CreateSolidBrush(GetShadow(PAPER_COLOR, factor)); // Brush for the Shadow, using the shadow color

		// Smaller rectangle coordinates for the cutout
		RECT rectShading = {
			rectMain.left + BORDER_EFFECT_SIZE, // left
			rectMain.top + BORDER_EFFECT_SIZE, // top
			rectMain.right - BORDER_EFFECT_SIZE, // right
			rectMain.bottom - BORDER_EFFECT_SIZE }; // bottom

		FillRect(hdc, &rectShading, brushShading);

		//Then, the "Paper" by drawing it with the paper color
		HBRUSH brushPaper = CreateSolidBrush(PAPER_COLOR); // Brush for the cutout, using the paper background color

		// Smaller rectangle coordinates for the cutout
		RECT rectCutout = {
			rectMain.left + BORDER_EFFECT_SIZE * 2, // left
			rectMain.top + BORDER_EFFECT_SIZE * 2, // top
			rectMain.right - BORDER_EFFECT_SIZE, // right
			rectMain.bottom - BORDER_EFFECT_SIZE }; // bottom

		FillRect(hdc, &rectCutout, brushPaper);

		// Clean up
		DeleteObject(brushMain);
		DeleteObject(brushShading);
		DeleteObject(brushPaper);
	}

	RECT ScreenToClientRect(HWND hWnd, RECT rect)
	{
		POINT topLeft = { rect.left, rect.top };
		POINT bottomRight = { rect.right, rect.bottom };

		ScreenToClient(hWnd, &topLeft);
		ScreenToClient(hWnd, &bottomRight);

		RECT clientRect = { topLeft.x, topLeft.y, bottomRight.x, bottomRight.y };
		return clientRect;
	}
};