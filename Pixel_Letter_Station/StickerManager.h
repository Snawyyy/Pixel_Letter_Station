#pragma once
#include <windows.h>
#include <shobjidl.h> // For IFileDialog, CLSID_FileOpenDialog, IID_IFileDialog, FOS_PICKFOLDERS
#include <objbase.h> // For CoInitialize and CoUninitialize
#include <vector>
#include <iostream>
#include "CustomWindowUI.h"
#include "Sticker.h"

#pragma comment(lib, "Ole32.lib")

using namespace std;

LRESULT StickerMenu(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void CreateStickerButtons(HWND hwnd, int width, int height, const vector<wstring>& bitmapFiles);

BOOL EnumChildProc(HWND hwndChild, LPARAM lParam);

wstring PickFolderAndReturnPath();

vector<wstring> GetBitmapFiles(wstring folderPath);

bool StorePathConfig(wstring directoryPath);

wstring ReadFileIntoWString(const wstring& filePath);
