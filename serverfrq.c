#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define PORT 8080
#define DATA "Hello, Client!"

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
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    double frequency = 2.0; // Frequency in Hz
    double interval = frequency_to_time(frequency) * 1000000; // Time in microseconds
    long long current_time;
    char buffer[1024];

    // Create server socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening...\n");

    // Accept a client connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    printf("Connection established with client.\n");

    // Send data at defined frequency with timestamp
    while (1) {
        current_time = get_current_time_us(); // Get current time
        snprintf(buffer, sizeof(buffer), "%lld %s", current_time, DATA); // Attach timestamp to data
        send(new_socket, buffer, strlen(buffer), 0);
        printf("Data sent at frequency: %.2f Hz with timestamp %lld\n", frequency, current_time);
        usleep((int)interval); // Sleep for the interval
    }

    return 0;
}
