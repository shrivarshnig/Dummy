#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

#define CLIENT_PORT 6321
#define IP ("127.0.0.1")

int main() {
    int client_sock;
    struct sockaddr_in server_addr;
    char buffer[1024];
    struct timespec sleep_time1 = {0};
    int frequency1 = 1;

    // Create a socket
    client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock < 0) {
        perror("Error in socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(CLIENT_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Connect to the server
    if (connect(client_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error in connection");
        exit(1);
    }

    // Receive data from the server
    sleep_time1.tv_nsec = 1000000000 / frequency1;
    while (1)
    {
        recv(client_sock, buffer, sizeof(buffer), 0);
        printf("Server: %s\n", buffer);
        nanosleep(&sleep_time1, NULL);
    }

    // Close the socket
    close(client_sock);

    return 0;
}
