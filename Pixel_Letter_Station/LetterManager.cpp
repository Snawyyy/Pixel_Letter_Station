#include "LetterManager.h"

HBITMAP GetLetter(HWND hWnd)
{
    HDC hdcWindow = GetDC(hWnd);
    HDC hdcMemDC = CreateCompatibleDC(hdcWindow);

    RECT rcClient;
    GetClientRect(hWnd, &rcClient);
    int width = rcClient.right - rcClient.left;
    int height = rcClient.bottom - rcClient.top;

    HBITMAP hbmScreen = CreateCompatibleBitmap(hdcWindow, width, height);
    HGDIOBJ oldBitmap = SelectObject(hdcMemDC, hbmScreen);

    BitBlt(hdcMemDC, 0, 0, LETTER_BOX_WIDTH + (SMALL_MARGIN * 2) - 2, height - (MARGIN * 2.5), hdcWindow, width - LETTER_BOX_WIDTH - MARGIN - SMALL_MARGIN, WIN_BAR_SIZE + MARGIN, SRCCOPY);

    // Cleanup: Only delete the memory DC and release the window DC.
    SelectObject(hdcMemDC, oldBitmap); // Restore the old bitmap
    DeleteDC(hdcMemDC);
    ReleaseDC(hWnd, hdcWindow);

    // Return the created bitmap
    return hbmScreen;
}

vector<BYTE> SerializeBitmap(HBITMAP hBitmap)
{
    BITMAP bitmapInfo;
    vector<BYTE> bitmapData;

    GetObject(hBitmap, sizeof(BITMAP), &bitmapInfo);

    DWORD pixelDataSize = bitmapInfo.bmHeight * bitmapInfo.bmWidthBytes;

    bitmapData.reserve(sizeof(BITMAP) + pixelDataSize); // Reserves space for the pixel data and the bitmap information

    bitmapData.insert(bitmapData.end(), reinterpret_cast<BYTE*>(&bitmapInfo), reinterpret_cast<BYTE*>(&bitmapInfo) + sizeof(BITMAP)); // Adds bitmap information to the vector

    // Gets the pixel data and add it to the vector
    vector<BYTE> pixelData(pixelDataSize);
    GetBitmapBits(hBitmap, pixelDataSize, pixelData.data());
    bitmapData.insert(bitmapData.end(), pixelData.begin(), pixelData.end());

    return bitmapData;
}

HBITMAP DeserializeBitmap(const vector<BYTE>& bitmapData)
{
    if (bitmapData.empty())
        return NULL;

    // Get the BITMAP structure from the serialized data
    const BITMAP* bitmapInfo = reinterpret_cast<const BITMAP*>(bitmapData.data());

    // Create a compatible DC
    HDC hdcScreen = GetDC(NULL);
    HDC hdcMemDC = CreateCompatibleDC(hdcScreen);
    ReleaseDC(NULL, hdcScreen);

    // Create a bitmap and select it into the compatible DC
    HBITMAP hBitmap = CreateBitmap(bitmapInfo->bmWidth, bitmapInfo->bmHeight, bitmapInfo->bmPlanes, bitmapInfo->bmBitsPixel, NULL);
    HGDIOBJ oldBitmap = SelectObject(hdcMemDC, hBitmap);

    // Copy the pixel data into the bitmap
    const BYTE* pixelData = bitmapData.data() + sizeof(BITMAP);
    SetBitmapBits(hBitmap, bitmapInfo->bmHeight * bitmapInfo->bmWidthBytes, pixelData);

    // Clean up
    SelectObject(hdcMemDC, oldBitmap);
    DeleteDC(hdcMemDC);

    return hBitmap;
}