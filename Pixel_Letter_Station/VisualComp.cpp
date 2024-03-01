#include "VisualComp.h"

bool QuitButton(LPARAM lParam) // GUI Quit Button
{
	LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
	if (pDIS->CtlID == QuitHMENU) { // Matching the HMENU value you passed when creating the button

		BOOL isPressed = pDIS->itemState & ODS_SELECTED;

		// Set the background and text colors
		SetTextColor(pDIS->hDC, RGB(0, 0, 0));
		SetBkColor(pDIS->hDC, RGB(255, 150, 100));
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

bool Title(HWND hWnd, int centerW) // The title of the application in the GUI
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	// Custom drawing code goes here
	HFONT hFont = CreateFont(
		20,               // Height of the font
		0,                     // Average character width (0 lets the system choose the best value)
		0,                     // Angle of escapement
		0,                     // Base-line orientation angle
		FW_EXTRABOLD,               // Font weight (FW_BOLD for bold)
		FALSE,                 // Italic attribute option
		FALSE,                 // Underline attribute option
		FALSE,                 // Strikeout attribute option
		ANSI_CHARSET,          // Character set identifier
		OUT_DEFAULT_PRECIS,    // Output precision
		CLIP_DEFAULT_PRECIS,   // Clipping precision
		DEFAULT_QUALITY,       // Output quality
		DEFAULT_PITCH | FF_SWISS, // Pitch and family
		L"Arial");              // Font name
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

	SetTextColor(hdc, RGB(0, 0, 0));// text color
	SetBkMode(hdc, TRANSPARENT); // To make background transparent
	TextOut(hdc, centerW - 70, 20, L"Pixel Letter Station", strlen("Pixel Letter Station"));
	EndPaint(hWnd, &ps);
	return 0; // Indicate we handled the message
}

bool DefaultButton(LPARAM lParam, const wchar_t* Text) // GUI Default Button
{
	LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
	if (pDIS->CtlID == DefaultHMENU) { // Matching the HMENU value you passed when creating the button

		BOOL isPressed = pDIS->itemState & ODS_SELECTED;

		// Set the background and text colors
		SetTextColor(pDIS->hDC, RGB(0, 0, 0));
		SetBkColor(pDIS->hDC, RGB(255, 255, 255));
		FillRect(pDIS->hDC, &pDIS->rcItem, CreateSolidBrush(RGB(255, 255, 255)));

		// Prepare the rectangle for the text, adjusting if the button is pressed
		RECT textRect = pDIS->rcItem;
		if (isPressed) {
			// Offset the textRect and change color to simulate the text moving when pressed
			OffsetRect(&textRect, 1, 1);
			SetTextColor(pDIS->hDC, RGB(255, 255, 255));
			SetBkColor(pDIS->hDC, RGB(200, 200, 255));
			FillRect(pDIS->hDC, &pDIS->rcItem, CreateSolidBrush(RGB(200, 200, 255)));
		}

		// Draw the button text using the adjusted rectangle
		DrawText(pDIS->hDC, Text, -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		// Draw a border around the button
		FrameRect(pDIS->hDC, &pDIS->rcItem, CreateSolidBrush(RGB(255, 255, 255)));

		return TRUE; // Indicate we handled the message
	}
}
