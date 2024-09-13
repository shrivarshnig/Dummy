#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/time.h>
#include<time.h>
#include <pthread.h>

// #define PORT  10069
#define IP ("127.0.0.1")

typedef struct {
    uint8_t send_command;
   
}server_send_t;

void* client(void* arg)
{ 
    printf("client\n");
    socklen_t addr_size;
    struct sockaddr_in ats_clientaddress;
    int sockfd;
    struct timespec sleep_time1 = {0};
    struct timespec trig_time;
    
    addr_size=sizeof(ats_clientaddress); 
    int port = *((int*)arg);

    /*Socket creation*/
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd<0)
    {
      printf("error in socket creation");
    }

    printf("socket creation is successful\n");

    /*Assigning port number and IP_ADDRESS*/
    ats_clientaddress.sin_family = AF_INET;
    ats_clientaddress.sin_addr.s_addr = inet_addr(IP);
    ats_clientaddress.sin_port = htons(port);

    /*Connect to the client*/
    if (connect(sockfd, (struct sockaddr *)&ats_clientaddress,sizeof(ats_clientaddress)) == -1) 
    {
        perror("Connection failed");
        exit(1);
    }
    printf("connected successfully\n");

    server_send_t receive;

    printf("got successfully\n");

    // for (int i = 0; i < 10000; i++)
    while( 1)
    {
        if (port = 6321)
        {
            int frequency1 = 2000;
            // sleep_time1.tv_sec = 0;
            // sleep_time1.tv_nsec = 1000000000 / frequency1;

            uint64_t period = (uint64_t)(1000000000/frequency1);
	        trig_time.tv_sec = period/1000000000;
	        trig_time.tv_nsec = period%1000000000;

            int num_bytes1=recv(sockfd,(void*)&receive,sizeof(server_send_t),0);

            if(num_bytes1 != sizeof(receive))
            {
                perror("Error in receiving size\n");

                // exit(1);

            }
            if(num_bytes1 == -1)
            {
                perror("Error in receiving\n");
                exit(1);

            }
            nanosleep(&trig_time, NULL);

            printf("the value is %d\n",receive.send_command);
        }
    }
    close(sockfd);
}

int main() 
{
    int ports[] = {6321};
    int num_ports = sizeof(ports) / sizeof(ports[0]);
    pthread_t client_threads[num_ports];

    // Create threads to connect to each server port
    for (int i = 0; i < num_ports; i++) {
        pthread_create(&client_threads[i], NULL, client, (void*)&ports[i]);
    }

    // Wait for all client threads to finish
    for (int i = 0; i < num_ports; i++) {
        pthread_join(client_threads[i], NULL);
    }

    return 0;
}