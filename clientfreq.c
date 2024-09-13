#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define PORT 8080
#define BUFFER_SIZE 1024

// Function to convert frequency to time interval
double frequency_to_time(double frequency) {
    return 1.0 / frequency;
}

// Function to get current time in microseconds
long long get_current_time_us() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000LL + tv.tv_usec;
}

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    long long server_time, client_time;
    char message[BUFFER_SIZE];
    double frequency = 2.0; // Expected frequency in Hz
    double interval = frequency_to_time(frequency) * 1000000; // Convert to microseconds
    double elapsed;

    // Create client socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    printf("Connected to server.\n");

    // Receive data and check timestamps
    while (1) {
        if (recv(sock, buffer, BUFFER_SIZE, 0) > 0) {
            sscanf(buffer, "%lld %[^\n]", &server_time, message); // Extract server time and message
            client_time = get_current_time_us(); // Get current client time

            // Calculate time difference between server send time and client receive time
            elapsed = (client_time - server_time) / 1000000.0; // Convert to seconds

            printf("Received data: %s | Server Time: %lld | Elapsed: %.6f seconds\n", message, server_time, elapsed);

            // Check if the elapsed time is within expected range
            if (elapsed < frequency_to_time(frequency) * 0.9 || elapsed > frequency_to_time(frequency) * 1.1) {
                printf("Frequency mismatch! Expected: %.2f Hz\n", frequency);
                break; // Stop if frequency doesn't match
            }

            memset(buffer, 0, sizeof(buffer)); // Clear buffer
        }
    }

    close(sock);
    return 0;
}
