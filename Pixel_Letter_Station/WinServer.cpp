#include "WinServer.h"

SOCKET InitializeServer()
{
    WSADATA wsaData;
    int result;

    // Request Winsock version 2.2
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (result != 0) //Checks if Initializing succeeded
    {
        MessageBox(NULL, L"WSAStartup failed\n", L"Fail", MB_OK);
    }
    else
    {
        cout << "WSAStartup succeeded\n";
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //creates ServerSocket
    if (serverSocket == INVALID_SOCKET) {
        cout << "Error at socket(): " << WSAGetLastError() << "\n";
        WSACleanup();
        return NULL;
    }

    //ServerSocket info and Binding
    struct sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(ServerIpAddress);
    service.sin_port = htons(ServerPort);

    if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
        cout << "bind() failed.\n";
        closesocket(serverSocket);
        return NULL;
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        cout << "Error listening on socket.\n";
        closesocket(serverSocket);
    }


    SOCKET clientSocket = accept(serverSocket, NULL, NULL); //Accepts clients sockets that are trying to connect
    if (clientSocket == INVALID_SOCKET) {
        cout << "Error at socket(): " << WSAGetLastError() << "\n";
        WSACleanup();
        return NULL;
    }
    else
    {
        cout << "client Created" << '\n';
        return clientSocket;
    }
}

SOCKET ConnectToServer()
{
    WSADATA wsaData;
    int result;

    // Request Winsock version 2.2
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (result != 0) //Checks if Initializing succeeded
    {
        MessageBox(NULL, L"WSAStartup failed\n", L"Fail", MB_OK);
    }
    else
    {
        cout << "WSAStartup succeeded\n";
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Creates the client socket
    if (clientSocket == INVALID_SOCKET) {
        cout << "Error at socket(socket): " << WSAGetLastError() << "\n";
        WSACleanup();
        return NULL;
    }
    //ServerSocket info for Binding
    struct sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(ServerIpAddress);
    service.sin_port = htons(ServerPort);

    result = connect(clientSocket, (SOCKADDR*)&service, sizeof(service));//Connecting to Server socket
    if (result == SOCKET_ERROR)
    {
        cout << "Error at socket(connect): " << WSAGetLastError() << "\n";
        WSACleanup();
        return NULL;
    }
    else
    {
        cout << "Connected" << "\n";
        return clientSocket;
    }
}

vector<BYTE> RecvData(SOCKET socket)
{

    // Receives the size
    int size = 0;
    int bytesReceived = 0;
    while (bytesReceived < sizeof(int))
    {
        int received = recv(socket, reinterpret_cast<char*>(&size) + bytesReceived, sizeof(int) - bytesReceived, 0);
        if (received == SOCKET_ERROR)
        {
            cout << "Failed to receive size. Error: " << WSAGetLastError() << endl;
            return vector<BYTE>();
        }
        else if (received == 0)
        {
            cout << "Connection closed by the peer." << endl;
            return vector<BYTE>();
        }
        bytesReceived += received;
    }
    vector<BYTE> recvData(size); // buffer

    if (bytesReceived != sizeof(int))
    {
            cout << "Failed to receive data" << '\n';
            return vector<BYTE>();
    }

    // Receives the bitmap data
    bytesReceived = 0;
    int remaining = size;
    while (remaining > 0)
    {
        int received = recv(socket, reinterpret_cast<char*>(recvData.data()) + bytesReceived, remaining, 0);
        if (received == SOCKET_ERROR)
        {
            cout << "Failed to receive bitmap data. Error: " << WSAGetLastError() << endl;
            return recvData;
        }
        else if (received == 0)
        {
            cout << "Connection closed by the peer." << endl;
            return recvData;
        }
        bytesReceived += received;
        remaining -= received;
    }

    cout << "Bitmap data received successfully." << endl;
    return recvData;
}

void SendData(SOCKET socket, vector<BYTE> Data)
{
    // sends size first
    int size = Data.size();
    send(socket, reinterpret_cast<const char*>(&size), sizeof(int), 0);

    // sends data
    int bytesSent = send(socket, (const char*)Data.data(),size, 0);
    if (bytesSent == SOCKET_ERROR) {
        cout << "Failed to send data. Error code: " << WSAGetLastError() << endl;
    }
    else {
        cout << "Successfully sent " << bytesSent << " bytes." << endl;
    }
}