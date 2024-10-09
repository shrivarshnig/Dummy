// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <arpa/inet.h>
// #include<sys/time.h>
// #include <time.h>

// #define PORT 12346
// #define TARGET_RATE_MBPS 40
// #define BUFFER_SIZE 8192  // 8 KB buffer

// // Function to send data at a specified rate
// // void send_data(int conn) {
// //     char buffer[BUFFER_SIZE] = {"hii"};
// //     long target_rate_bps = (TARGET_RATE_MBPS * 1000000) / 8;  // Convert to bytes per second
// //     long total_bytes_sent = 0;
// //   struct timeval start_time, end_time;
// //       long elapsed_time;


// //     gettimeofday(&start_time, NULL);

// //     while (total_bytes_sent < target_rate_bps) {
// //         ssize_t bytes_sent = send(conn, (void*)&buffer, sizeof(buffer), 0);
// //         if (bytes_sent < 0) {
// //             perror("send failed");
// //             break;
// //         }
// //         total_bytes_sent += bytes_sent;


// //         // Control the sending rate
// //         gettimeofday(&end_time, NULL);
// //         elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);

// //        if (total_bytes_sent >= target_rate_bps) {
// //             if (elapsed_time < 1000000) {  // 1 second in microseconds
// //                 usleep(1000000 - elapsed_time);  // Sleep to maintain 1-second intervals
// //             }        }
// //         printf("%s\n",buffer);
// //     }

// //     printf("Sent %ld bytes at %ld Mbps.\n", total_bytes_sent, TARGET_RATE_MBPS);
// // }

// int main() {
//     int server_fd, new_socket;
//     struct sockaddr_in address;
//     int addrlen = sizeof(address);
//         char buffer[BUFFER_SIZE];
//             long total_bytes_received = 0;



//     // Create socket
//     if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
//         perror("socket failed");
//         exit(EXIT_FAILURE);
//     }

//     // Setup the address structure
//     address.sin_family = AF_INET;
//     address.sin_addr.s_addr = INADDR_ANY;
//     address.sin_port = htons(PORT);

//     // Bind the socket
//     if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
//         perror("bind failed");
//         close(server_fd);
//         exit(EXIT_FAILURE);
//     }

//     // Listen for connections
//     if (listen(server_fd, 3) < 0) {
//         perror("listen failed");
//         close(server_fd);
//         exit(EXIT_FAILURE);
//     }

//     printf("Server listening on port %d\n", PORT);

//     // Accept incoming connections
//     while (1) {
//         new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
//         if (new_socket < 0) {
//             perror("accept failed");
//             continue;
//         }
//     }

//         printf("Connected to client\n");
        
//         ssize_t bytes_received = recv(new_socket, buffer, BUFFER_SIZE, 0);
//         if (bytes_received <= 0) {
//            exit(1);
//         }
//         total_bytes_received += bytes_received;
   

//     printf("Received %ld bytes.\n", total_bytes_received);

    

//     close(server_fd);
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include<sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 12346
#define TARGET_RATE_MBPS 40
#define BUFFER_SIZE 8192  // 8 KB buffer
typedef struct {
    uint8_t send_command;
    
}sends;

// Function to receive data at a specified rate
void receive_data(int conn) {
    char buffer[BUFFER_SIZE];
    long target_rate_bps = 81920;  // Convert to bytes per second
    long total_bytes_received = 0;
    long elapsed_time;

    struct timeval start_time, end_time;
// sends receive;
    while (1) {
            gettimeofday(&start_time, NULL);

        ssize_t bytes_received = recv(conn, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            if (bytes_received == 0) {
                // Connection closed by client
                printf("Client disconnected.\n");
            } else {
                perror("recv failed");
            }
            break;
        }

        total_bytes_received += bytes_received;
        //  gettimeofday(&end_time, NULL);
         
            //   elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);

        
         printf("Received %ld bytes. Total received: %ld bytes\n", bytes_received, total_bytes_received);
    }
//     printf("the start time is %d\n",start_time);
//         printf("the start time is %d\n",end_time);

// printf("the elapsed time is %ld\n",elapsed_time);
    printf("Received a total of %ld bytes at %ld Mbps.\n", total_bytes_received, TARGET_RATE_MBPS);
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

