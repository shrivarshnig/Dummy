#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include<time.h>
#include<sys/time.h>

#define PORT 12346
#define BUFFER_SIZE 4096*2 // 8 KB buffer
#define TARGET_RATE_MBPS 81920

typedef struct {
    uint8_t send_command;
   
}server_send_t;

int main() {
    int sock;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE] = {"hii"};
    long total_bytes_sent = 0;
    struct timespec trig_time;

        long target_rate_bps = 8192;  // Convert to bytes per second


    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }
    printf("socket is created\n");

    // Define server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        return -1;
    }
    printf("connected\n");

    while (total_bytes_sent < target_rate_bps) {
                    int frequency = 10;


                ssize_t bytes_received = send(sock, buffer, BUFFER_SIZE, 0);

        if (bytes_received <= 0) {
            // break;
        }
        total_bytes_sent += bytes_received;
    printf("send %ld bytes.\n", total_bytes_sent);
    }
    close(sock);
    return 0;
}

