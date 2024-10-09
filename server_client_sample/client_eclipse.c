#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

//#pragma comment(lib, "ws2_32.lib") // Link with ws2_32.lib
// windows

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 12345

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;
    char message[100];
    int recv_size;
    char server_reply[2000];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code : %d\n", WSAGetLastError());
        return 1;
    }

    // Create a socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket : %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    printf("Socket created.\n");

    // Setup the server address structure
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Connect failed with error code : %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    printf("Connected to server.\n");

    // Send some data
//    strcpy(message, "Hello Server");
//    if (send(sock, message, strlen(message), 0) == SOCKET_ERROR) {
//        printf("Send failed with error code : %d\n", WSAGetLastError());
//        closesocket(sock);
//        WSACleanup();
//        return 1;
//    }
//    printf("Data sent.\n");
//
//    // Receive a reply from the server
//    recv_size = recv(sock, server_reply, sizeof(server_reply) - 1, 0);
//    if (recv_size == SOCKET_ERROR) {
//        printf("Receive failed with error code : %d\n", WSAGetLastError());
//    } else {
//        server_reply[recv_size] = '\0'; // Null-terminate the received data
//        printf("Server reply: %s\n", server_reply);
//    }

    // Clean up
//    closesocket(sock);
    WSACleanup();

    return 0;
}

