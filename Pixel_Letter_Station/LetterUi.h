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
        struct BrushDeleter {
            void operator()(HBRUSH brush) { DeleteObject(brush); }
        };

        std::unique_ptr<HBRUSH__, BrushDeleter> brushMain(CreateSolidBrush(LETTER_BORDER));
        FillRect(hdc, &rectMain, brushMain.get());

        RECT rectShading = {
            rectMain.left + BORDER_EFFECT_SIZE,
            rectMain.top + BORDER_EFFECT_SIZE,
            rectMain.right - BORDER_EFFECT_SIZE,
            rectMain.bottom - BORDER_EFFECT_SIZE
        };

        std::unique_ptr<HBRUSH__, BrushDeleter> brushShading(CreateSolidBrush(GetShadow(PAPER_COLOR, factor)));
        FillRect(hdc, &rectShading, brushShading.get());

        RECT rectCutout = {
            rectMain.left + BORDER_EFFECT_SIZE * 2,
            rectMain.top + BORDER_EFFECT_SIZE * 2,
            rectMain.right - BORDER_EFFECT_SIZE,
            rectMain.bottom - BORDER_EFFECT_SIZE
        };

        std::unique_ptr<HBRUSH__, BrushDeleter> brushPaper(CreateSolidBrush(PAPER_COLOR));
        FillRect(hdc, &rectCutout, brushPaper.get());
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