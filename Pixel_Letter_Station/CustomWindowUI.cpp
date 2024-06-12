#include "CustomWindowUI.h"

LRESULT CALLBACK UserButton(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HBRUSH hBrush = NULL;
	static RECT rect;
	PAINTSTRUCT ps;
	HDC hdc;
	static bool isPressed;

	switch (msg)
	{
	case WM_CREATE:
	{
		// Creates a solid brush for the button background color
		hBrush = CreateSolidBrush(UI_BORDER); // Change the RGB values to set your desired background color
		break;
	}
	case WM_SIZE:
	{
		// Stores the button's client area dimensions
		GetClientRect(hwnd, &rect);

		// Create a circular region based on the updated client rect
		HRGN hRgn = CreateEllipticRgn(0, 0, rect.right, rect.bottom);
		SetWindowRgn(hwnd, hRgn, TRUE); // Set the window region. TRUE to redraw the window immediately

		// NOTE: The region is now owned by the system, no need to call DeleteObject on hRgn
		break;
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);

		// Create the outer and inner rectangles
		RECT outerRect = { 0, 0, rect.right, rect.bottom };
		RECT innerRect = { BORDER_EFFECT_SIZE, BORDER_EFFECT_SIZE, rect.right - BORDER_EFFECT_SIZE, rect.bottom - BORDER_EFFECT_SIZE };

		// Create the outer and inner regions
		HRGN outerRgn = CreateEllipticRgnIndirect(&outerRect);
		HRGN innerRgn = CreateEllipticRgnIndirect(&innerRect);

		// Combine the regions to create a ring shape
		CombineRgn(outerRgn, outerRgn, innerRgn, RGN_DIFF);
		if (isPressed)
		{
			// Set the brush color for the outer ring
			HBRUSH outerBrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, outerBrush);

			// Fill the outer ring
			FillRgn(hdc, outerRgn, outerBrush);

			// Set the brush color for the inner circle
			HBRUSH innerBrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, innerBrush);

			// Fill the inner circle
			Ellipse(hdc, innerRect.left, innerRect.top, innerRect.right, innerRect.bottom);
			FillRgn(hdc, innerRgn, innerBrush);
			// Clean up the brushes and regions
			DeleteObject(outerBrush);
			DeleteObject(innerBrush);
		}
		else
		{
			// Set the brush color for the outer ring
			HBRUSH outerBrush = CreateSolidBrush(UI_BORDER);
			SelectObject(hdc, outerBrush);

			// Fill the outer ring
			FillRgn(hdc, outerRgn, outerBrush);

			// Set the brush color for the inner circle
			HBRUSH innerBrush = CreateSolidBrush(UI_BORDER_SHADOW);
			SelectObject(hdc, innerBrush);

			// Fill the inner circle
			Ellipse(hdc, innerRect.left, innerRect.top, innerRect.right, innerRect.bottom);
			FillRgn(hdc, innerRgn, innerBrush);
			// Clean up the brushes and regions
			DeleteObject(outerBrush);
			DeleteObject(innerBrush);
		}
		DeleteObject(outerRgn);
		DeleteObject(innerRgn);

		// Draw the button text centered in the circle
		SetBkMode(hdc, TRANSPARENT);
		DrawText(hdc, L"Button", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		EndPaint(hwnd, &ps);
		break;


	}
	case WM_MOUSEMOVE:
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_LEAVE; // Specifies that we want a WM_MOUSELEAVE message when the mouse leaves
		tme.hwndTrack = hwnd;
		tme.dwHoverTime = HOVER_DEFAULT; // Not needed for WM_MOUSELEAVE but required to be set

		TrackMouseEvent(&tme); // Call this function to start tracking

		break;
	}
	case WM_MOUSELEAVE:
	{
		// The mouse has left the window, you can handle it here
		isPressed = FALSE; // Reset the isPressed state if needed
		InvalidateRect(hwnd, NULL, TRUE); // Redraw the window if necessary

		break;
	}
	case WM_LBUTTONDOWN:
	{
		// Update the button's pressed state
		isPressed = TRUE;
		// Invalidate the button to trigger a redraw
		InvalidateRect(hwnd, NULL, TRUE);

		break;
	}
	case WM_LBUTTONUP:
	{
		// Update the button's pressed state
		isPressed = FALSE;
		SendMessage(GetParent(hwnd), WM_COMMAND, (WPARAM)7, (LPARAM)hwnd);
		// Invalidate the button to trigger a redraw
		InvalidateRect(hwnd, NULL, TRUE);

		break;
	}
	case WM_DESTROY:
	{
		// Clean up resources
		DeleteObject(hBrush);
		break;
	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}

void RichTextBoxPaint(HWND box)
{
	PARAFORMAT2 pf;
	memset(&pf, 0, sizeof(PARAFORMAT2)); // formatting the richbox text
	pf.cbSize = sizeof(PARAFORMAT2);
	pf.dwMask = PFM_LINESPACING;
	pf.bLineSpacingRule = 5;
	pf.dyLineSpacing = 30;

	SendMessage(box, EM_SETBKGNDCOLOR, 0, (LPARAM)PAPER_COLOR); // BKG color
	SendMessage(box, EM_SETPARAFORMAT, 0, (LPARAM)&pf); // Sends format
	SendMessage(box, EM_SETLIMITTEXT, (WPARAM)1400, 0); // Sends Text char limit

}

LRESULT CALLBACK StickerMenuButton(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP hBitmap = NULL; // Handle to the button's bitmap
	PAINTSTRUCT ps;
	HDC hdc, hdcMem;
	BITMAP bitmap;
	HGDIOBJ oldBitmap;

	RECT rcClient;
	GetClientRect(hwnd, &rcClient);

	int width = rcClient.right - rcClient.left;
	int height = rcClient.bottom - rcClient.top;

	switch (msg)
	{
	case WM_CREATE:
	{
		CREATESTRUCT* pCreateStruct = (CREATESTRUCT*)lParam;
		hBitmap = (HBITMAP)pCreateStruct->lpCreateParams;

		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)hBitmap);

		break;
	}
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		hBitmap = (HBITMAP)GetWindowLongPtr(hwnd, GWLP_USERDATA);

		if (hBitmap != NULL) 
		{
			hdcMem = CreateCompatibleDC(hdc);
			oldBitmap = SelectObject(hdcMem, hBitmap);

			// Retrieve the dimensions of the bitmap
			GetObject(hBitmap, sizeof(bitmap), &bitmap);
			StretchBlt(hdc, 0, 0, width, height, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

			// Cleanup
			SelectObject(hdcMem, oldBitmap);
			DeleteDC(hdcMem);
		}
		else
		{
			MessageBox(hwnd, L"failed loading", L"", MB_OK);
		}

		EndPaint(hwnd, &ps);
		break;

	case WM_LBUTTONDOWN:
	{
		// Action to take when the button is clicked
		HINSTANCE hInstance = GetModuleHandle(NULL);
		hBitmap = (HBITMAP)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		HWND hwndSticker = CreateSticker(GetParent(GetParent(hwnd)), hInstance, 0, 0, 30, hBitmap);
		SendMessage(hwndSticker, WM_NCLBUTTONDOWN, HTCAPTION, 0);

		break;
	}
	case WM_DESTROY:
	{
		// Remove the bitmap handle from the window's memory
		SetWindowLongPtr(hwnd, GWLP_USERDATA, 0);
		DeleteObject(hBitmap);

		break;
	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}