#include<stdint.h>
#include<stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

//#pragma comment(lib, "ws2_32.lib") // Link with ws2_32.lib

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 10069
typedef struct {
    uint8_t send_command;

}server_send_t;

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d\n", WSAGetLastError());
        return 1;
    }

    // Create a socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
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
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Connect failed with error code : %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    server_send_t receive;

    printf("Connected to server.\n");
    //receive the command from the client

    int num_bytes1=recv(sock,(void*)&receive,sizeof(server_send_t),0);

    if(num_bytes1<=0)
    {
       perror("Error in receiving\n");
       exit(1);

    }
    printf("the value is %d\n",receive.send_command);
    return 0;
}

