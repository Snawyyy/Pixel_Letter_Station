// Pixel_Letter_Station.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Window.h"
using namespace std;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//int main()
{
    cout << "Creating window\n";

    Window* pWindow = new Window();

    bool running = true;
    while (running)
    {
        if (!pWindow->ProcessMessages())
        {
            cout << "Closing window\n";
            running = false;
        }

        Sleep(10);
    }

    delete pWindow;

    return 0;
}

