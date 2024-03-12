#pragma once
#include <iostream>
#include "Windows.h"
#include "CustomWindowUI.h"
#include <vector>


using namespace std;

SOCKET InitializeServer();
SOCKET ConnectToServer();
vector<BYTE> RecvData(SOCKET socket);
void SendData(SOCKET socket, vector<BYTE> Data);

void AsyncRecvData(SOCKET socket, HWND letterContents);


//Server Settings
#define ServerIpAddress "127.0.0.1"
#define ServerPort 777