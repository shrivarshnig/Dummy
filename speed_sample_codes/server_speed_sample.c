#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 12346
#define TARGET_RATE_MBPS 20
#define BUFFER_SIZE 8192  // 8 KB buffer
typedef struct {
    uint8_t send_command;
    
}sends;

// Function to send data at a specified rate
void receive_data(int conn) {
    char buffer[BUFFER_SIZE]; 
    // = {"hii"};
    long target_rate_bps = (40*(1000000))/8;  // Convert to bytes per second
    long total_bytes_received = 0;
    clock_t start_time = clock();
sends receive;
    while (total_bytes_received < target_rate_bps) {
        ssize_t bytes_sent = recv(conn, buffer, BUFFER_SIZE, 0);
        if (bytes_sent < 0) {
            perror("send failed");
            break;
        }
        total_bytes_received += bytes_sent;


        // Control the sending rate
        // clock_t elapsed_time = clock() - start_time;
        // double elapsed_seconds = (double)elapsed_time / CLOCKS_PER_SEC;

        // if (elapsed_seconds > 0) {
        //     double expected_time = (double)total_bytes_sent / target_rate_bps;
        //     usleep((useconds_t)((expected_time - elapsed_seconds) * 1e6));
        // }
         printf("%s\n",buffer);
        // printf("%d\n",receive.send_command);
    }

    printf("Received %ld bytes at %ld Mbps.\n", total_bytes_received, TARGET_RATE_MBPS);
}   

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Setup the address structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // Accept incoming connections
    while (1) {
        new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept failed");
            continue;
        }

        printf("Connected to client\n");
        receive_data(new_socket);
        close(new_socket);
        printf("Connection closed\n");
    }

    close(server_fd);
    return 0;
}


