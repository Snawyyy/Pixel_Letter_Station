#include "StickerManager.h"

LRESULT CALLBACK StickerMenu(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HBRUSH hBrush = NULL;
    static RECT rect;
    PAINTSTRUCT ps;
    HDC hdc = NULL;
    static bool isPressed;

    RECT rcClient;
    GetClientRect(hwnd, &rcClient);

    int width = rcClient.right - rcClient.left;
    int height = rcClient.bottom - rcClient.top;

    static wstring folderPath;
    static vector<wstring> bitmapFiles;
    int index = 0;

    switch (msg)
    {
    case WM_CREATE:
    {
        // Test
        HWND button = CreateWindowA("BUTTON",
            "Test",
            WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
            (width / 2) - ((width - BORDER_EFFECT_SIZE * 2) / 2), height - BUTTON_HEIGHT - BORDER_EFFECT_SIZE, width - BORDER_EFFECT_SIZE * 2, BUTTON_HEIGHT,
            hwnd, (HMENU)6, NULL, NULL);

        folderPath = ReadFileIntoWString(L"config.txt");

        if (!folderPath.empty())
        {
            bitmapFiles = GetBitmapFiles(folderPath);
            CreateStickerButtons(hwnd, width, height, bitmapFiles);
        }

        break;
    }
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case 6:
        {
            // get folder path and store it
            wstring folderPath = PickFolderAndReturnPath();
            StorePathConfig(folderPath);

            // create sticker buttons, and get rid of old ones
            bitmapFiles = GetBitmapFiles(folderPath);
            if (bitmapFiles.size() != 0)
            {
                EnumChildWindows(hwnd, EnumChildProc, 0);
            CreateStickerButtons(hwnd, width, height, bitmapFiles);
            }
            else
            {
                EnumChildWindows(hwnd, EnumChildProc, 0);
            }
            // update the window
            UpdateWindow(hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        }
        break;
    }
    case WM_DRAWITEM:
    {
        Button button(lParam, 6, L"Pick Folder");
        button.Draw(DEFULT_BUTTON_COLOR, RGB(0, 0, 0));

        break;
    }
    case WM_PAINT:
    {
        hdc = BeginPaint(hwnd, &ps);

        RECT backgroundRect;
        GetWindowRect(hWnd, &backgroundRect);

        LetterUi Letter(hdc, hWnd);
        Letter.Draw(backgroundRect);

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

void CreateStickerButtons(HWND hwnd, int width, int height,const vector<wstring>& bitmapFiles)
{
    int bitmapHeight = height / 16;
    int y = MARGIN;

    for (size_t i = 0; i < bitmapFiles.size(); i++)
    {
        if (y + bitmapHeight + SMALL_MARGIN * 2 + MARGIN < height)
        {
            HBITMAP hbmSticker = (HBITMAP)LoadImage(NULL, bitmapFiles[i].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
            if (hbmSticker)
            {
                //MessageBox(hwnd, bitmapFiles[i].c_str(), L"beep", MB_OK);
                BITMAP bitmapInfo;
                GetObject(hbmSticker, sizeof(BITMAP), &bitmapInfo);
                int stickerWidth = (bitmapInfo.bmWidth * bitmapHeight) / bitmapInfo.bmHeight;

                HINSTANCE hInstance = GetModuleHandle(NULL);
                HWND StickerButton = CreateWindowEx(
                    0,
                    L"StickerButton",
                    L"Button",
                    WS_CHILD | WS_VISIBLE,
                    width / 2 - stickerWidth / 2, y, stickerWidth, bitmapHeight,
                    hwnd,
                    NULL,
                    hInstance,
                    (LPVOID)hbmSticker
                );
                y += bitmapHeight + SMALL_MARGIN;
            }
        }
    }
}


BOOL CALLBACK EnumChildProc(HWND hwndChild, LPARAM lParam)
{
    // Get the class name of the child window
    wchar_t className[256];
    GetClassNameW(hwndChild, className, 256);

    // Check if the class name matches "StickerButton"
    if (wcscmp(className, L"StickerButton") == 0)
    {
        // If it matches, destroy the child window
        DestroyWindow(hwndChild);
    }

    // Always return TRUE to continue enumeration
    return TRUE;
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

vector<wstring> GetBitmapFiles(wstring folderPath)
{
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

bool StorePathConfig(wstring directoryPath)
{
    // Create (or open if it already exists) a file
    HANDLE hFile = CreateFile(
        L"config.txt",          // File name
        GENERIC_WRITE,     // Open for writing
        0,                 // Do not share
        NULL,              // Default security
        CREATE_ALWAYS,     // Overwrite existing
        FILE_ATTRIBUTE_NORMAL, // Normal file
        NULL);             // No template

    if (hFile == INVALID_HANDLE_VALUE) {
        // Failed to open or create the file
        MessageBox(NULL, L"Failed to create Config file.", L"Error", MB_OK);
        return false;
    }

    DWORD bytesWritten;
    DWORD strLength = static_cast<DWORD>(directoryPath.length() * sizeof(wchar_t));

    BOOL writeResult = WriteFile(
        hFile,                           // Handle to the file
        directoryPath.c_str(),           // Buffer to write from
        strLength,                       // Number of bytes to write
        &bytesWritten,                   // Number of bytes written
        NULL                             // Not overlapped I/O
    );

    if (!writeResult) {
        // Failed to write to the file
        MessageBox(NULL, L"Failed to write to the Config.", L"Error", MB_OK);
    }

    // Close the file handle
    CloseHandle(hFile);

    return true;
}

wstring ReadFileIntoWString(const wstring& filePath) {
    // Open the file
    HANDLE hFile = CreateFileW(filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        // Handle error (e.g., display an error message or throw an exception)
        return wstring();
    }

    // Get the file size
    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(hFile, &fileSize)) {
        CloseHandle(hFile);
        // Handle error
        return wstring();
    }

    // Read the file in chunks
    const DWORD bufferSize = 4096; // Adjust this value as needed
    vector<wchar_t> buffer(bufferSize);
    wstring fileContents;
    DWORD bytesRead;
    do {
        if (!ReadFile(hFile, buffer.data(), bufferSize * sizeof(wchar_t), &bytesRead, NULL)) {
            CloseHandle(hFile);
            // Handle error
            return wstring();
        }
        fileContents.append(buffer.data(), bytesRead / sizeof(wchar_t));
    } while (bytesRead == bufferSize * sizeof(wchar_t));

    CloseHandle(hFile);
    return fileContents;
}