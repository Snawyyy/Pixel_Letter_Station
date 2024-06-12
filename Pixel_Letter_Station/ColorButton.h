#pragma once
#include "Button.h"

class ColorButtonA : public Button
{
public:
	LPARAM lParam;
	LPDRAWITEMSTRUCT pDIS;
	int buttonId;
	const wchar_t* text;

	ColorButtonA(LPARAM lp, int id, const wchar_t* te):Button(lp, id, te), lParam(lp), buttonId(id), text(te)
	{
		pDIS = (LPDRAWITEMSTRUCT)lParam;
	}
	void DrawBorder() override
	{
		HPEN hPen = CreatePen(PS_SOLID, BORDER_EFFECT_SIZE, LETTER_BORDER);

		// Select the pen and a null brush into the DC
		HPEN hOldPen = (HPEN)SelectObject(pDIS->hDC, hPen);
		HBRUSH hOldBrush = (HBRUSH)SelectObject(pDIS->hDC, GetStockObject(NULL_BRUSH));

		// Draw the rectangle
		Rectangle(pDIS->hDC, 0, 0, pDIS->rcItem.right, pDIS->rcItem.bottom);
	}
};