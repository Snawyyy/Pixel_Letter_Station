#pragma once
#include <iostream>
#include "Windows.h"
#include <vector>


using namespace std;

SOCKET InitializeServer();
SOCKET ConnectToServer();
string RecvData(SOCKET clientSocket);
void SendData(SOCKET socket, vector<char>& buffer);

void AsyncRecvData(SOCKET socket);


//Server Settings
#define ServerIpAddress "127.0.0.1"
#define ServerPort 777