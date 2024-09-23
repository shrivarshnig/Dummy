// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <arpa/inet.h>

// #define PORT 12346
// #define BUFFER_SIZE 8192  // 8 KB buffer

// int main() {
//     int sock;
//     struct sockaddr_in server_address;
//     char buffer[BUFFER_SIZE];
//     long total_bytes_received = 0;

//     // Create socket
//     if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
//         perror("Socket creation error");
//         return -1;
//     }
//     printf("socket is created\n");

//     // Define server address
//     server_address.sin_family = AF_INET;
//     server_address.sin_port = htons(PORT);
//     server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

//     // Connect to the server
//     if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
//         perror("Connection failed");
//         return -1;
//     }
//     printf("connected\n");

//     // Receive data
//     while (1) {
//         ssize_t bytes_received = recv(sock, buffer, BUFFER_SIZE, 0);
//         if (bytes_received <= 0) {
//             break;
//         }
//         total_bytes_received += bytes_received;
//     }

//     printf("Received %ld bytes.\n", total_bytes_received);

//     close(sock);
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<sys/types.h>
#include <arpa/inet.h>
#include <time.h>
#include<sys/time.h>
#define PORT 12346
#define BUFFER_SIZE 8192  // 8 KB buffer
#define TARGET_RATE_MBPS 40

int main() {
    int sock;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];
    long total_bytes_received = 0;

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }
    printf("Socket is created\n");

    // Define server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        return -1;
    }
    printf("Connected\n");

    // Calculate target rate
    long target_rate_bps = (TARGET_RATE_MBPS * 1000000) / 8;  // Convert to bytes per second
    clock_t start_time = clock();

    // Receive data
    while (1) {
        ssize_t bytes_received = recv(sock, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            break;
        }
        total_bytes_received += bytes_received;

        // Control the receiving rate
        clock_t elapsed_time = clock() - start_time;
        double elapsed_seconds = (double)elapsed_time / CLOCKS_PER_SEC;
        double expected_time = (double)total_bytes_received / target_rate_bps;

        // Sleep if we have exceeded the expected time
        if (elapsed_seconds < expected_time) {
            usleep((useconds_t)((expected_time - elapsed_seconds) * 1e6));
        }
    }

    printf("Received %ld bytes at approximately %ld Mbps.\n", total_bytes_received, TARGET_RATE_MBPS);

    close(sock);
    return 0;
}
