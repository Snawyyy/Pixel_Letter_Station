#include "StickerManager.h"

LRESULT CALLBACK StickerMenu(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HBRUSH hBrush = NULL;
    static RECT rect;
    PAINTSTRUCT ps;
    HDC hdc;
    static bool isPressed;

    vector<wstring> bitmapFiles;

    switch (msg)
    {
    case WM_CREATE:
    {
        vector<wstring> bitmapFiles = GetBitmapFiles();
        MessageBox(hwnd, bitmapFiles[0].c_str(), L"", MB_OK);
        break;
    }
    case WM_PAINT:
    {
        hdc = BeginPaint(hwnd, &ps);

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