#include "CustomWindowUI.h"

bool QuitButton(LPARAM lParam) // Bar Quit Button
{
	LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
	if (pDIS->CtlID == QUIT_BUTTON_ID) { // Matching the HMENU value you passed when creating the button

		BOOL isPressed = pDIS->itemState & ODS_SELECTED;

		// Set the background and text colors
		SetTextColor(pDIS->hDC, RGB(0, 0, 0));
		SetBkMode(pDIS->hDC, TRANSPARENT);
		FillRect(pDIS->hDC, &pDIS->rcItem, CreateSolidBrush(RGB(255, 0, 0)));

		// Button shading
		RECT effectRect;

		// Shadow
		SetRect(&effectRect, pDIS->rcItem.left, pDIS->rcItem.bottom - BORDER_EFFECT_SIZE, pDIS->rcItem.right, pDIS->rcItem.bottom);
		FillRect(pDIS->hDC, &effectRect, CreateSolidBrush(RGB(100, 0, 0)));
		SetRect(&effectRect, pDIS->rcItem.right - BORDER_EFFECT_SIZE, pDIS->rcItem.top, pDIS->rcItem.right, pDIS->rcItem.bottom);
		FillRect(pDIS->hDC, &effectRect, CreateSolidBrush(RGB(100, 0, 0))); 

		// Shine
		SetRect(&effectRect, pDIS->rcItem.left, pDIS->rcItem.top, pDIS->rcItem.right, pDIS->rcItem.top + BORDER_EFFECT_SIZE); 
		FillRect(pDIS->hDC, &effectRect, CreateSolidBrush(RGB(255, 100, 100))); 
		SetRect(&effectRect, pDIS->rcItem.left, pDIS->rcItem.top, pDIS->rcItem.left + BORDER_EFFECT_SIZE, pDIS->rcItem.bottom); 
		FillRect(pDIS->hDC, &effectRect, CreateSolidBrush(RGB(255, 100, 100))); 

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
		DrawText(pDIS->hDC, L"X", -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		FrameRect(pDIS->hDC, &pDIS->rcItem, CreateSolidBrush(RGB(100, 0, 0))); // Draw the border around the button


		return TRUE; // Indicate we handled the message
	}
}

bool MinimizeButton(LPARAM lParam) // Bar Minimize Button
{
	LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
	if (pDIS->CtlID == MINIMIZE_BUTTON_ID) { // Matching the HMENU value you passed when creating the button

		BOOL isPressed = pDIS->itemState & ODS_SELECTED;

		// Set the background and text colors
		SetTextColor(pDIS->hDC, RGB(0, 0, 0));
		SetBkMode(pDIS->hDC, TRANSPARENT);
		FillRect(pDIS->hDC, &pDIS->rcItem, CreateSolidBrush(RGB(255, 250, 215)));

		// Button shading
		RECT effectRect;

		// Shadow
		SetRect(&effectRect, pDIS->rcItem.left, pDIS->rcItem.bottom - BORDER_EFFECT_SIZE, pDIS->rcItem.right, pDIS->rcItem.bottom);
		FillRect(pDIS->hDC, &effectRect, CreateSolidBrush(RGB(160, 120, 95)));
		SetRect(&effectRect, pDIS->rcItem.right - BORDER_EFFECT_SIZE, pDIS->rcItem.top, pDIS->rcItem.right, pDIS->rcItem.bottom);
		FillRect(pDIS->hDC, &effectRect, CreateSolidBrush(RGB(160, 120, 95)));

		// Shine
		SetRect(&effectRect, pDIS->rcItem.left, pDIS->rcItem.top, pDIS->rcItem.right, pDIS->rcItem.top + BORDER_EFFECT_SIZE);
		FillRect(pDIS->hDC, &effectRect, CreateSolidBrush(RGB(255, 240, 200)));
		SetRect(&effectRect, pDIS->rcItem.left, pDIS->rcItem.top, pDIS->rcItem.left + BORDER_EFFECT_SIZE, pDIS->rcItem.bottom);
		FillRect(pDIS->hDC, &effectRect, CreateSolidBrush(RGB(255, 240, 200)));

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
		DrawText(pDIS->hDC, L"-", -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		FrameRect(pDIS->hDC, &pDIS->rcItem, CreateSolidBrush(RGB(100, 0, 0))); // Draw the border around the button


		return TRUE; // Indicate we handled the message
	}
}

bool DefaultButton(LPARAM lParam, const wchar_t* Text, int buttonId) // GUI Default Button
{
	LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
	if (pDIS->CtlID == buttonId) { // Matching the HMENU value you passed when creating the button

		BOOL isPressed = pDIS->itemState & ODS_SELECTED;

		// Set the background and text colors
		SetTextColor(pDIS->hDC, RGB(0, 0, 0));
		SetBkMode(pDIS->hDC, TRANSPARENT);
		FillRect(pDIS->hDC, &pDIS->rcItem, CreateSolidBrush(RGB(255, 255, 255)));

		// Button shading
		RECT effectRect;

		// Shadow
		SetRect(&effectRect, pDIS->rcItem.left, pDIS->rcItem.bottom - BORDER_EFFECT_SIZE, pDIS->rcItem.right, pDIS->rcItem.bottom);
		FillRect(pDIS->hDC, &effectRect, CreateSolidBrush(RGB(160, 120, 95)));
		SetRect(&effectRect, pDIS->rcItem.right - BORDER_EFFECT_SIZE, pDIS->rcItem.top, pDIS->rcItem.right, pDIS->rcItem.bottom);
		FillRect(pDIS->hDC, &effectRect, CreateSolidBrush(RGB(160, 120, 95)));

		// Shine
		SetRect(&effectRect, pDIS->rcItem.left, pDIS->rcItem.top, pDIS->rcItem.right, pDIS->rcItem.top + BORDER_EFFECT_SIZE);
		FillRect(pDIS->hDC, &effectRect, CreateSolidBrush(RGB(255, 240, 200)));
		SetRect(&effectRect, pDIS->rcItem.left, pDIS->rcItem.top, pDIS->rcItem.left + BORDER_EFFECT_SIZE, pDIS->rcItem.bottom);
		FillRect(pDIS->hDC, &effectRect, CreateSolidBrush(RGB(255, 240, 200)));

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
		FrameRect(pDIS->hDC, &pDIS->rcItem, CreateSolidBrush(RGB(0, 0, 0))); // Draw the border around the button

		return TRUE; // Indicate we handled the message
	}
}

bool Title(HDC hdc, HWND hWnd, int centerW) // The title of the application in the GUI
{
	// Custom drawing code goes here
	HFONT hFont = CreateFont(
		TITLE_SIZE,               // Height of the font
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
	TextOut(hdc, BAR_MARGIN, ((WIN_BAR_SIZE / 2) - (TITLE_SIZE / 2)), L"Pixel Letter Station", strlen("Pixel Letter Station"));
	return 0; // Indicate we handled the message
}


void WindowBar(HDC hdc, HWND hWnd, int width)
{
	// Set the color for the rectangle (optional)
	HBRUSH brush = CreateSolidBrush(RGB(255, 100, 100)); // orangeish color
	HPEN nullPen = CreatePen(PS_NULL, 1, RGB(0, 0, 0)); // Null pen, color doesn't matter
	SelectObject(hdc, brush);
	SelectObject(hdc, nullPen);

	// Draw the rectangle
	// Parameters: HDC, left, top, right, bottom
	Rectangle(hdc, 0, 0, width, WIN_BAR_SIZE);

	// Draw the Border Shadow
	brush = CreateSolidBrush(RGB(155, 0, 0)); // orangeish color
	SelectObject(hdc, brush);
	Rectangle(hdc, 0, WIN_BAR_SIZE, width, WIN_BAR_SIZE - BORDER_EFFECT_SIZE);
	Rectangle(hdc, width - BORDER_EFFECT_SIZE + 1, 0, width + 1, WIN_BAR_SIZE);

	// Draw the Border shine
	brush = CreateSolidBrush(RGB(255, 200, 200)); // orangeish color
	SelectObject(hdc, brush);
	Rectangle(hdc, 0, 0, width, BORDER_EFFECT_SIZE);
	Rectangle(hdc, 0, 0, BORDER_EFFECT_SIZE, WIN_BAR_SIZE);



	// Clean up
	DeleteObject(brush);
	DeleteObject(nullPen);
}

void WindowFrame(HDC hdc, HWND hWnd, int width, int height)
{
	// First, draw the larger rectangle with a solid color
	HBRUSH brushMain = CreateSolidBrush(RGB(255, 100, 100)); // Orangeish color for the main rectangle
	RECT rectMain = { 0, 0, width, height }; // Main rectangle coordinates
	FillRect(hdc, &rectMain, brushMain);

	// Then, "cut out" a shape by drawing it with the background color
	HBRUSH brushCutout = CreateSolidBrush(RGB(255, 250, 215)); // Brush for the cutout, using the window background color
	RECT rectCutout = { 5, 5, width - 5, height -5 }; // Smaller rectangle coordinates for the cutout
	FillRect(hdc, &rectCutout, brushCutout);

	// Clean up
	DeleteObject(brushMain);
	DeleteObject(brushCutout);
}
