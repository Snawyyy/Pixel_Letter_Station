#include "CustomWindowUI.h"

bool QuitButton(LPARAM lParam, int buttonId) // Bar Quit Button
{
	LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;

	if (pDIS->CtlID == buttonId) // Matching the HMENU value passed when creating the button
	{
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
	else
	{
		return FALSE;
	}
}

bool MinimizeButton(LPARAM lParam) // Bar Minimize Button
{
	LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
	if (pDIS->CtlID == MINIMIZE_BUTTON_ID) // Matching the HMENU value passed when creating the button
	{ 

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
			SetBkColor(pDIS->hDC, RGB(200, 200, 255));
			FillRect(pDIS->hDC, &pDIS->rcItem, CreateSolidBrush(RGB(200, 200, 255)));
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
	if (pDIS->CtlID == buttonId)// Matching the HMENU value passed when creating the button
	{

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
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, L"C:\\Users\\Snawy\\source\\repos\\Snawyyy\\Pixel_Letter_Station\\Images\\LOGO.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (hBitmap == NULL)
	{
		MessageBox(NULL, L"Load Failed", L"Fail", MB_OK);
	}
	HDC hdcMem = CreateCompatibleDC(hdc);
	HGDIOBJ oldBitmap = SelectObject(hdcMem, hBitmap);

	BITMAP bitmap;
	GetObject(hBitmap, sizeof(BITMAP), &bitmap);
	StretchBlt(hdc, SMALL_MARGIN + BORDER_EFFECT_SIZE, (WIN_BAR_SIZE / 2) - ((bitmap.bmHeight / 2) / 2), (bitmap.bmWidth / 2), (bitmap.bmHeight / 2), hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

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
	TextOut(hdc, MARGIN * 2, ((WIN_BAR_SIZE / 2) - (TITLE_SIZE / 2)), L"Pixel Letter Station", strlen("Pixel Letter Station"));
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
	Rectangle(hdc, 0, 0, width + 1, BORDER_EFFECT_SIZE);
	Rectangle(hdc, 0, 0, BORDER_EFFECT_SIZE, WIN_BAR_SIZE);



	// Clean up
	DeleteObject(brush);
	DeleteObject(nullPen);
}

void WindowFrame(HDC hdc, HWND hWnd, int width, int height)
{
	// Create a pen of desired thickness and color
	HPEN hPen = CreatePen(PS_SOLID, BAR_MARGIN * 2, RGB(255, 100, 100)); // Black pen

	// Select the pen and a null brush into the DC
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

	// Draw the rectangle
	Rectangle(hdc, 0, 0, width, height);

	// Restore the original pen and brush
	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldBrush);

	// Clean up
	DeleteObject(hPen);
}

void LetterBackground(HDC hdc, HWND hWnd, int width, int height)
{
	// First, draw the larger rectangle with a solid color
	HBRUSH brushMain = CreateSolidBrush(RGB(50, 0, 0)); // Black color for the Border
	RECT rectMain = { width - LETTER_BOX_WIDTH - MARGIN - SMALL_MARGIN, MARGIN * 2.5, width - (SMALL_MARGIN * 2), height - (MARGIN * 3)}; // Main rectangle coordinates
	FillRect(hdc, &rectMain, brushMain);

	//Then, the "Paper" by drawing it with the paper color
	HBRUSH brushShading = CreateSolidBrush(RGB(200, 160, 50)); // Brush for the Shadow, using the shadow color
	RECT rectShading = { (width - (LETTER_BOX_WIDTH / 2) - MARGIN + BORDER_EFFECT_SIZE) - (LETTER_BOX_WIDTH / 2) - SMALL_MARGIN, (MARGIN * 2.5) + BORDER_EFFECT_SIZE, width - (SMALL_MARGIN * 2) - BORDER_EFFECT_SIZE, height - (MARGIN * 3) - BORDER_EFFECT_SIZE }; // Smaller rectangle coordinates for the cutout
	FillRect(hdc, &rectShading, brushShading);

	//Then, the "Paper" by drawing it with the paper color
	HBRUSH brushPaper = CreateSolidBrush(RGB(255, 223, 133)); // Brush for the cutout, using the paper background color
	RECT rectCutout = { (width - (LETTER_BOX_WIDTH / 2) - MARGIN + (BORDER_EFFECT_SIZE * 2)) - (LETTER_BOX_WIDTH / 2) - SMALL_MARGIN, (MARGIN * 2.5) + (BORDER_EFFECT_SIZE * 2), width - (SMALL_MARGIN * 2) - BORDER_EFFECT_SIZE, height - (MARGIN * 3) - BORDER_EFFECT_SIZE }; // Smaller rectangle coordinates for the cutout
	FillRect(hdc, &rectCutout, brushPaper);

	// Clean up
	DeleteObject(brushMain);
	DeleteObject(brushShading);
	DeleteObject(brushPaper);
}

void RichTextBoxPaint(HWND box)
{
	PARAFORMAT2 pf;
	memset(&pf, 0, sizeof(PARAFORMAT2)); // formatting the richbox text
	pf.cbSize = sizeof(PARAFORMAT2);
	pf.dwMask = PFM_LINESPACING;
	pf.bLineSpacingRule = 5;
	pf.dyLineSpacing = 30;

	SendMessage(box, EM_SETBKGNDCOLOR, 0, (LPARAM)RGB(255, 223, 133)); // BKG color
	SendMessage(box, EM_SETPARAFORMAT, 0, (LPARAM)&pf); // Sends format
	SendMessage(box, EM_SETLIMITTEXT, (WPARAM)1400, 0); // Sends Text char limit

}

void ServerStatusBar(HDC hdc, int isConnected)
{
	// First, draw the larger rectangle with a solid color
	HBRUSH brushMain = CreateSolidBrush(RGB(50, 0, 0)); // Black color for the Border
	RECT rectMain = { MARGIN * 1.5, MARGIN * 2.5, MARGIN * 10, (MARGIN * 4) + SMALL_MARGIN }; // Main rectangle coordinates
	FillRect(hdc, &rectMain, brushMain);

	//Then, the "Shine" by drawing it with the Shine color
	HBRUSH brushShading = CreateSolidBrush(RGB(150, 100, 70)); // Brush for the cutout, using the Shine color
	RECT rectShading = { MARGIN * 1.5 + BORDER_EFFECT_SIZE, MARGIN * 2.5 + BORDER_EFFECT_SIZE, MARGIN * 10 - BORDER_EFFECT_SIZE, (MARGIN * 4) + SMALL_MARGIN - BORDER_EFFECT_SIZE }; // Smaller rectangle coordinates for the cutout
	FillRect(hdc, &rectShading, brushShading);

	//Then, the "Paper" by drawing it with the paper color
	HBRUSH brushPaper = CreateSolidBrush(RGB(100, 50, 50)); // Brush for the cutout, using the window background color
	RECT rectCutout = { MARGIN * 1.5 + (BORDER_EFFECT_SIZE * 2), MARGIN * 2.5 + (BORDER_EFFECT_SIZE * 2), MARGIN * 10 - BORDER_EFFECT_SIZE, (MARGIN * 4) + SMALL_MARGIN - BORDER_EFFECT_SIZE }; // Smaller rectangle coordinates for the cutout
	FillRect(hdc, &rectCutout, brushPaper);


	// Custom drawing code goes here
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
		DEFAULT_QUALITY,       // Output quality
		DEFAULT_PITCH | FF_SWISS, // Pitch and family
		L"Arial");              // Font name
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

	SetTextColor(hdc, RGB(255, 255, 255));// text color
	SetBkMode(hdc, TRANSPARENT); // To make background transparent
	TextOut(hdc, MARGIN * 2, MARGIN * 3, L"Status:", strlen("Status:"));
	if (isConnected == 0)
	{
		SetTextColor(hdc, RGB(255, 100, 100));// text color
		TextOut(hdc, MARGIN * 5, MARGIN * 3, L"Offline", strlen("Offline"));
	}
	if (isConnected == 1)
	{
		SetTextColor(hdc, RGB(100, 255, 100));// text color
		TextOut(hdc, MARGIN * 5, MARGIN * 3, L"Connected", strlen("Connected"));
	}
	if (isConnected == 2)
	{
		SetTextColor(hdc, RGB(150, 150, 255));// text color
		TextOut(hdc, MARGIN * 5, MARGIN * 3, L"server", strlen("server"));
	}

	// Clean up
	DeleteObject(brushMain);
	DeleteObject(brushShading);
	DeleteObject(brushPaper);

	return;

}