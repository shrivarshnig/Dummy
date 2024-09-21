#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080
#define BUFFER_SIZE 512  // Size of the buffer for sending data
#define DATA_RATE 5000000 // 5 MBps (40 Mbps = 5 MBps)

void send_data(int socket) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 'A', BUFFER_SIZE); // Fill buffer with dummy data
    char ack[4]; // Buffer for acknowledgment message

    struct timespec req = {0}, rem = {0};
    req.tv_sec = 0;
    req.tv_nsec = (BUFFER_SIZE * 8 * 1000000000) / DATA_RATE; // Calculate sleep time

    size_t total_bytes_sent = 0;
    time_t start_time = time(NULL);

    while (1) {
        // Send data
        if (send(socket, buffer, BUFFER_SIZE, 0) < 0) {
            perror("Send failed");
            break;
        }
        total_bytes_sent += BUFFER_SIZE;

        // Wait for acknowledgment
        ssize_t bytes_received = recv(socket, ack, sizeof(ack) - 1, 0);
        if (bytes_received > 0) {
            ack[bytes_received] = '\0'; // Null-terminate the ACK
            if (strcmp(ack, "ACK") == 0) {
                printf("Acknowledgment received\n");
            }
        } else {
            perror("Receive ACK failed");
            break;
        }

        // Sleep to control sending rate
        nanosleep(&req, &rem);

        // Calculate the sending rate every second
        time_t current_time = time(NULL);
        if (current_time - start_time >= 1) {
            double speed = (total_bytes_sent * 8) / (1024.0 * 1024.0); // Speed in Mbps
            printf("Sending rate: %.2f Mbps\n", speed);
            total_bytes_sent = 0; // Reset for the next interval
            start_time = current_time; // Reset start time
        }
    }
}

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address / Address not supported");
        return -1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return -1;
    }

    send_data(sock);

    close(sock);
    return 0;
}
