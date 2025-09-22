// client.cpp
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

#define PORT         8080
#define BUFFER_SIZE  1024

int main() {
    WSADATA wsa{};
    SOCKET sock = INVALID_SOCKET;
    sockaddr_in server{};
    char buffer[BUFFER_SIZE]{};

    // Init Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        cerr << "Failed. Error Code: " << WSAGetLastError() << "\n";
        return 1;
    }

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        cerr << "Could not create socket: " << WSAGetLastError() << "\n";
        WSACleanup();
        return 1;
    }

    // Server details
    server.sin_family = AF_INET;
    server.sin_port   = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr); // localhost

    // Connect
    if (connect(sock, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        cerr << "Connection error\n";
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // ---- Send filename ----
    string filename = "received.txt";
    if (send(sock, filename.c_str(), (int)filename.size(), 0) == SOCKET_ERROR) {
        cerr << "send filename failed\n";
        closesocket(sock); WSACleanup(); return 1;
    }

    // Read server ack
    int n = recv(sock, buffer, BUFFER_SIZE - 1, 0);
    if (n <= 0) { cerr << "recv ack failed\n"; closesocket(sock); WSACleanup(); return 1; }
    buffer[n] = '\0';
    cout << "Server: " << buffer << "\n";

    // ---- Send file content (example payload) ----
    string myData = "Welcome to Crypto Lab";
    if (send(sock, myData.c_str(), (int)myData.size(), 0) == SOCKET_ERROR) {
        cerr << "send content failed\n";
        closesocket(sock); WSACleanup(); return 1;
    }

    // Read final ack
    memset(buffer, 0, sizeof(buffer));
    n = recv(sock, buffer, BUFFER_SIZE - 1, 0);
    if (n > 0) {
        buffer[n] = '\0';
        cout << "Server: " << buffer << "\n";
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
