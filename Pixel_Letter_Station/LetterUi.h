#pragma once
#include "Ui.h"

class LetterUi:Ui
{
public:
	HDC hdc;

	LetterUi(HDC hd, HWND hWnd) :Ui(hWnd), hdc(hd)
	{

	}

	void Draw()
	{
		LetterBackground(hdc, hWnd);
	}

	void LetterBackground(HDC hdc, HWND hWnd)
	{
		// First, draw the border, a larger rectangle with a solid color
		HBRUSH brushMain = CreateSolidBrush(LETTER_BORDER); // Black color for the Border

		// Main rectangle rect
		RECT rectMain = {
			LETTER_BOX_RECT_LEFT, // left
			LETTER_BOX_RECT_TOP, // top
			LETTER_BOX_RECT_RIGHT, // right
			LETTER_BOX_RECT_BOTTOM };  // bottom

		FillRect(hdc, &rectMain, brushMain);

		//Then, the "Shadow" by drawing it with the paper color
		HBRUSH brushShading = CreateSolidBrush(PAPER_COLOR_SHADOW); // Brush for the Shadow, using the shadow color

		// Smaller rectangle coordinates for the cutout
		RECT rectShading = {
			LETTER_BOX_RECT_LEFT + BORDER_EFFECT_SIZE, // left
			LETTER_BOX_RECT_TOP + BORDER_EFFECT_SIZE, // top
			LETTER_BOX_RECT_RIGHT - BORDER_EFFECT_SIZE, // right
			LETTER_BOX_RECT_BOTTOM - BORDER_EFFECT_SIZE }; // bottom

		FillRect(hdc, &rectShading, brushShading);

		//Then, the "Paper" by drawing it with the paper color
		HBRUSH brushPaper = CreateSolidBrush(PAPER_COLOR); // Brush for the cutout, using the paper background color

		// Smaller rectangle coordinates for the cutout
		RECT rectCutout = {
			LETTER_BOX_RECT_LEFT + BORDER_EFFECT_SIZE * 2, // left
			LETTER_BOX_RECT_TOP + BORDER_EFFECT_SIZE * 2, // top
			LETTER_BOX_RECT_RIGHT - BORDER_EFFECT_SIZE, // right
			LETTER_BOX_RECT_BOTTOM - BORDER_EFFECT_SIZE }; // bottom

		FillRect(hdc, &rectCutout, brushPaper);

		// Clean up
		DeleteObject(brushMain);
		DeleteObject(brushShading);
		DeleteObject(brushPaper);
	}
};