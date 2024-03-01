#include "VisualComp.h"

bool QuitButton(LPARAM lParam)
{
	LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
	if (pDIS->CtlID == QuitHMENU) { // Matching the HMENU value you passed when creating the button

		BOOL isPressed = pDIS->itemState & ODS_SELECTED;

		// Set the background and text colors
		SetBkColor(pDIS->hDC, RGB(255, 150, 100));
		SetTextColor(pDIS->hDC, RGB(0, 0, 0));
		FillRect(pDIS->hDC, &pDIS->rcItem, CreateSolidBrush(RGB(255, 150, 100)));

		// Prepare the rectangle for the text, adjusting if the button is pressed
		RECT textRect = pDIS->rcItem;
		if (isPressed) {
			// Offset the textRect and change color to simulate the text moving when pressed
			OffsetRect(&textRect, 1, 1);
			SetTextColor(pDIS->hDC, RGB(255, 255, 255));
			SetBkColor(pDIS->hDC, RGB(100, 0, 0));
			FillRect(pDIS->hDC, &pDIS->rcItem, CreateSolidBrush(RGB(100, 0, 0)));
		}

		// Draw the button text using the adjusted rectangle
		DrawText(pDIS->hDC, L"Quit", -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		// Draw a border around the button
		FrameRect(pDIS->hDC, &pDIS->rcItem, CreateSolidBrush(RGB(100, 0, 0)));

		return TRUE; // Indicate we handled the message
	}
}

