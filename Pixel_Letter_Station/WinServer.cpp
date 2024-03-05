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

string RecvData(SOCKET clientSocket)
{
    constexpr size_t BUFSIZE = 2560;
    char dataRecv[BUFSIZE] = {};

    int bytesReceived = recv(clientSocket, dataRecv, sizeof(dataRecv), 0); //If recived Anything, then
    if (bytesReceived > 0)
    {
        dataRecv[bytesReceived] = '\0';
        cout << "The Data:" << dataRecv << '\n';
        return dataRecv;
    }
    else if (bytesReceived == 0)
    {
        dataRecv[bytesReceived] = '\0';
        string receivedData(dataRecv);
        cout << "Disconnected" << '\n';
    }
    else
    {
        cout << "Failed" << '\n';
    }

}

void SendData(SOCKET socket, vector<char>& buffer)
{
    cout << buffer.data() << std::endl; // Output the converted string

    cout << "Sending data to client. Size: " << buffer.size() << " bytes." << endl;
    int bytesSent = send(socket, buffer.data(), buffer.size(), 0);
    if (bytesSent == SOCKET_ERROR) {
        cout << "Failed to send data. Error code: " << WSAGetLastError() << endl;
    }
    else {
        cout << "Successfully sent " << bytesSent << " bytes." << endl;
    }
}

void AsyncRecvData(SOCKET socket, HWND letterContents)
{
    string data = RecvData(socket);

    size_t size = data.size() + 1; // Size for wide char array

    std::vector<wchar_t> wbuffer(size);
    size_t convertedChars = 0;

    // Convert char to wchar_t safely
    errno_t err = mbstowcs_s(&convertedChars, wbuffer.data(), size, data.c_str(), _TRUNCATE);

    if (err != 0) {
        std::cerr << "Error converting string." << std::endl;
        return;
    }

    std::wcout << wbuffer.data() << std::endl; // Output the converted string
    SetWindowText(letterContents, wbuffer.data());

}