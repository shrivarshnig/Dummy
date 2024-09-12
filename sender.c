#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>


#define SERVER_PORT 6321
#define IP ("127.0.0.1")

int main() 
{
    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[1024];
    struct timespec sleep_time = {0};
    int frequency = 1;

	// Create a socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
    {
	    perror("Error in socket");
	    exit(1);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	// Bind the socket to the address and port
	if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) 
    {
	    perror("Error in binding");
	    exit(1);
	}
	printf("Server is listening...\n");

	// Listen for incoming connections
	listen(sockfd, 10);

    // Accept a new connection
    addr_size = sizeof(new_addr);
    new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);

	// Send data to the client
	strcpy(buffer, "Hello from the server!");
    sleep_time.tv_nsec = 1000000000 / frequency;
    for (int i = 0; i < 10; i++)
    {
	    send(new_sock, buffer, strlen(buffer), 0);
        nanosleep(&sleep_time, NULL);
    }

	// Close the sockets
	close(new_sock);
	close(sockfd);

	return 0;
}
