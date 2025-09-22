// server.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")   // Link Winsock library

using namespace std;

#define PORT         8080
#define BUFFER_SIZE  1024

int main() {
    WSADATA wsa{};
    SOCKET server_fd = INVALID_SOCKET, new_socket = INVALID_SOCKET;
    sockaddr_in server{}, client{};
    int c = 0;
    char buffer[BUFFER_SIZE] = {0};

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        cout << "Failed. Error Code: " << WSAGetLastError() << '\n';
        return 1;
    }

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == INVALID_SOCKET) {
        cout << "Could not create socket: " << WSAGetLastError() << '\n';
        WSACleanup();
        return 1;
    }

    // Prepare sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Bind
    if (bind(server_fd, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        cout << "Bind failed with error code: " << WSAGetLastError() << '\n';
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // Listen
    if (listen(server_fd, 3) == SOCKET_ERROR) {
        cout << "Listen failed with error code: " << WSAGetLastError() << '\n';
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }
    cout << "Server listening on port " << PORT << "...\n";

    // Accept connection
    c = sizeof(sockaddr_in);
    new_socket = accept(server_fd, (sockaddr*)&client, &c);
    if (new_socket == INVALID_SOCKET) {
        cout << "Accept failed with error code: " << WSAGetLastError() << '\n';
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // ---- Receive filename ----
    int n = recv(new_socket, buffer, BUFFER_SIZE - 1, 0);
    if (n <= 0) {
        cout << "Failed to receive filename.\n";
        closesocket(new_socket);
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }
    buffer[n] = '\0';
    string filename = buffer;
    cout << "Receiving file: " << filename << '\n';

    // Ack filename
    send(new_socket, "Filename received", (int)strlen("Filename received"), 0);

    // ---- Receive file content (until client closes) ----
    ofstream outfile(filename, ios::binary);
    if (!outfile) {
        cout << "Could not open output file.\n";
        closesocket(new_socket);
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // Clear buffer and continue reading bytes
    memset(buffer, 0, sizeof(buffer));
    while ((n = recv(new_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        outfile.write(buffer, n);
    }
    outfile.close();

    if (n == 0) {
        cout << "File transfer complete.\n";
    } else if (n < 0) {
        cout << "Receive error: " << WSAGetLastError() << '\n';
    }

    // Final ack
    send(new_socket, "File saved successfully", (int)strlen("File saved successfully"), 0);

    // Cleanup
    closesocket(new_socket);
    closesocket(server_fd);
    WSACleanup();
    return 0;
}
