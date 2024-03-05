#pragma once
#include <iostream>
#include "Windows.h"


using namespace std;

SOCKET InitializeServer();
SOCKET ConnectToServer();
string RecvData(SOCKET clientSocket);

//Server Settings
#define ServerIpAddress "127.0.0.1"
#define ServerPort 777