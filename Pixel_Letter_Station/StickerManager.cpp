#include "StickerManager.h"

LRESULT CALLBACK StickerMenu(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HBRUSH hBrush = NULL;
    static RECT rect;
    PAINTSTRUCT ps;
    HDC hdc;
    static bool isPressed;

    static vector<wstring> bitmapFiles;
    int index = 0;

    switch (msg)
    {
    case WM_CREATE:
    {
        bitmapFiles = GetBitmapFiles();
        break;
    }
    case WM_PAINT:
    {
        hdc = BeginPaint(hwnd, &ps);

        int bitmapWidth = 20;
        int bitmapHeight = 20;
        if (bitmapFiles.size() > 0)
        {

        // Load the bitmaps
        HBITMAP hbmSticker0 = (HBITMAP)LoadImage(NULL, bitmapFiles[index].c_str(), IMAGE_BITMAP, bitmapWidth, bitmapHeight, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
        HBITMAP hbmSticker1 = (HBITMAP)LoadImage(NULL, bitmapFiles[index + 1].c_str(), IMAGE_BITMAP, bitmapWidth, bitmapHeight, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
        HBITMAP hbmSticker2 = (HBITMAP)LoadImage(NULL, bitmapFiles[index + 1].c_str(), IMAGE_BITMAP, bitmapWidth, bitmapHeight, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

        // Draw the bitmaps
        if (hbmSticker0 && hbmSticker1 && hbmSticker2) {
            HDC hdc = GetDC(hwnd);
            HDC hdcMem = CreateCompatibleDC(hdc);

            int y = SMALL_MARGIN; // Initial y-coordinate

            // Draw the first bitmap
            SelectObject(hdcMem, hbmSticker0);
            BitBlt(hdc, 10, y, bitmapWidth, bitmapHeight, hdcMem, 0, 0, SRCCOPY);
            y += bitmapHeight + SMALL_MARGIN; // Update y-coordinate for the next bitmap

            // Draw the second bitmap
            SelectObject(hdcMem, hbmSticker1);
            BitBlt(hdc, 10, y, bitmapWidth, bitmapHeight, hdcMem, 0, 0, SRCCOPY);
            y += bitmapHeight + SMALL_MARGIN; // Update y-coordinate for the next bitmap

            // Draw the third bitmap
            SelectObject(hdcMem, hbmSticker2);
            BitBlt(hdc, 10, y, bitmapWidth, bitmapHeight, hdcMem, 0, 0, SRCCOPY);

            // Cleanup
            DeleteDC(hdcMem);
            ReleaseDC(hwnd, hdc);
        }

        }
        EndPaint(hwnd, &ps);
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


wstring PickFolderAndReturnPath() 
{
    wstring folderPath; // This will store the selected folder path

    // Initialize COM
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if (SUCCEEDED(hr)) {
        // Create the FileOpenDialog object
        IFileDialog* pfd = NULL;
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));
        if (SUCCEEDED(hr)) {
            // Set the options on the dialog (FOS_PICKFOLDERS to pick folders)
            DWORD dwOptions;
            hr = pfd->GetOptions(&dwOptions);
            if (SUCCEEDED(hr)) {
                hr = pfd->SetOptions(dwOptions | FOS_PICKFOLDERS);
                if (SUCCEEDED(hr)) {
                    // Show the dialog
                    hr = pfd->Show(NULL);
                    if (SUCCEEDED(hr)) {
                        // Obtain the result once the user clicks the 'Open' button.
                        IShellItem* psiResult;
                        hr = pfd->GetResult(&psiResult);
                        if (SUCCEEDED(hr)) {
                            // Get the path of the selected folder
                            PWSTR pszFilePath = NULL;
                            hr = psiResult->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                            if (SUCCEEDED(hr)) {
                                // Convert PWSTR to std::wstring and store it
                                folderPath = pszFilePath;
                                // Free the path string when done
                                CoTaskMemFree(pszFilePath);
                            }
                            psiResult->Release();
                        }
                    }
                }
            }
            pfd->Release();
        }
        CoUninitialize();
    }

    return folderPath; // Return the selected folder path
}

vector<wstring> GetBitmapFiles() 
{
    wstring folderPath = PickFolderAndReturnPath();
    vector<wstring> filePaths;

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile((folderPath + L"\\*.bmp").c_str(), &findFileData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            // Construct full file path and add it to the vector
            filePaths.push_back(folderPath + L"\\" + findFileData.cFileName);
        } while (FindNextFile(hFind, &findFileData) != 0);
        FindClose(hFind);
    }

    return filePaths;
}