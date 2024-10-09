// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <arpa/inet.h>
// #include<time.h>
// #include<sys/time.h>
// #define PORT 12346
// #define BUFFER_SIZE 8192  // 8 KB buffer
// #define TARGET_RATE_MBPS 40
//   static int i=0;
// void send_data(int conn);
// int main() {
//     int sock;
//     struct sockaddr_in server_address;

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
//    send_data(sock);
//     close(sock);
//     return 0;
// }
// void send_data(int conn) {
//     char buffer[BUFFER_SIZE] = {"hii"};
//     long target_rate_bps = (TARGET_RATE_MBPS * 1000000) / 8;  // Convert to bytes per second
//     long total_bytes_sent = 0;
//   struct timeval start_time, end_time;
//       long elapsed_time;


//     gettimeofday(&start_time, NULL);

//     while (total_bytes_sent < target_rate_bps) {
      
//         ssize_t bytes_sent = send(conn, (void*)&buffer, sizeof(buffer), 0);
//         if (bytes_sent < 0) {
//             perror("send failed");
//             break;
//         }
//         i++;
//         total_bytes_sent += bytes_sent;


//         // Control the sending rate
//         gettimeofday(&end_time, NULL);
//         elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);

//        if (total_bytes_sent >= target_rate_bps) {
//             if (elapsed_time < 1000000) {  // 1 second in microseconds
//                 usleep(1000000 - elapsed_time);  // Sleep to maintain 1-second intervals
//             }        }
//         printf("%s-%d\n",buffer,i);
//     }

//     printf("Sent %ld bytes at %ld Mbps.\n", total_bytes_sent, TARGET_RATE_MBPS);
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/time.h>

#define PORT 12346
#define BUFFER_SIZE 8192  // 8 KB buffer
#define TARGET_RATE_MBPS 40
typedef struct {
    uint8_t send_command;
    
}sends;


static int i = 0;  // Counter for messages

void send_data(int conn);

int main() {
    int sock;
    struct sockaddr_in server_address;

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

    // Send data to the server
    send_data(sock);

    // Close socket after sending data
    close(sock);
    return 0;
}

void send_data(int conn) {
    char buffer[BUFFER_SIZE] = {"hi"};  // Buffer to hold data
    long target_rate_bps = 81920;  // Convert target rate to bytes per second
    long total_bytes_sent = 0;
    struct timeval start_time, end_time;
    long elapsed_time;

    // Get start time
    // gettimeofday(&start_time, NULL);
    // sends sending={.send_command=20};
    // Loop to send data while maintaining the target rate
    while (total_bytes_sent < target_rate_bps) {
        // Send data
        ssize_t bytes_sent = send(conn, buffer,BUFFER_SIZE, 0);
        if (bytes_sent < 0) {
            perror("Send failed");
            break;
        }
        i++;  // Increment message counter
        total_bytes_sent += bytes_sent;

        // Get current time
        // gettimeofday(&end_time, NULL);

        // Calculate elapsed time in microseconds
        // elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);

        // Throttle the sending rate if necessary
        // if (total_bytes_sent >= target_rate_bps) {
        //     if (elapsed_time < 1000000) {  // Check if less than 1 second has passed
        //         usleep(1000000 - elapsed_time);  // Sleep to maintain a 1-second interval
        //     }
        // }

        // Output the buffer content and message count
        // printf("%s-%d\n", buffer, i);
                // printf("%d\n",sending.send_command);

    }

    // Output the total bytes sent and target rate
    printf("Sent %ld bytes at %ld Mbps.\n", total_bytes_sent, TARGET_RATE_MBPS);
}
