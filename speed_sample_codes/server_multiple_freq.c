#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/time.h>
#include <time.h>
#include <pthread.h>

// #define PORT  10069
#define IP ("127.0.0.1")
#define MAX_PORTS 5
#define BUFFER_SIZE 8192
#define TARGET_MBPS_1 8192
#define TARGET_MBPS_2 81920
typedef struct {
    uint8_t send_command;
    
}server_send_t;
 static int bytes_sent_1;
 static int bytes_sent_2;
   static long total_bytes_sent_1= 0;
   static long total_bytes_sent_2= 0;

void* server(void* arg)
{
 
    int e,n; 
    uint8_t hold;
    int serversocket,clientsocket;  
    struct sockaddr_in servaddr,clientaddr;
    socklen_t addr_size;
    int port = *((int*)arg);

    struct timespec sleep_time = {0};

    struct timespec trig_time;

    serversocket=socket(AF_INET,SOCK_STREAM,0);
    if(serversocket == -1)
    {
       printf("socket creation failed\n");
       exit(1);
    }
    printf("Socket successfully created\n");
        //assign IP Address

    servaddr.sin_family=AF_INET; 
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr=inet_addr(IP);

    printf("Before Binding\n");
    e=bind(serversocket,(struct sockaddr*)&servaddr,sizeof(servaddr));
    if(e<0)
    {
	    perror("Error in binding123\n");
	    exit(1);
    }
    printf("Binding Successful\n");
    n=listen(serversocket,10);
    if(n<0)
    {
	     perror("Failed to listen for connections\n");
	     exit(1);
    }
    addr_size=sizeof(clientaddr); 
    printf("Listening\n");

    // while(1)
    // {
        if(port == 6321)
        {
            clientsocket=accept(serversocket,(struct sockaddr*)&clientaddr,&addr_size);
            if(clientsocket<0)
            {
	            perror("error in accepting connection\n");
	            exit(1);
            }

            else
            {
	            printf("Sending\n");
                char buffer1[BUFFER_SIZE] = {"hii"};  // Buffer to hold data

                if(bytes_sent_1<TARGET_MBPS_1)
                {
                // sleep_time.tv_sec = 1;
                int frequency = 1;

                uint64_t period = (uint64_t)(1000000000/frequency);
	            trig_time.tv_sec = period/1000000000;
	            trig_time.tv_nsec = period%1000000000;

               

	                if(bytes_sent_1=send(clientsocket,buffer1,BUFFER_SIZE,0)==-1)
	                {
	                   perror("Error in sending\n");
	                }	
                    // nanosleep(&sleep_time, NULL);
                    if(nanosleep(&trig_time, NULL)==-1){
                        perror("Error in nanosleep\n");
                        exit(1);
                    }
                        total_bytes_sent_1+=bytes_sent_1;

                    // sleep(1);
                }
                    printf("Sent %ld bytes at %ld Mbps.\n", total_bytes_sent_1, TARGET_MBPS_1);

                }

            }  
        
        else if(port == 6322)
        {
            int frequency = 10;
            clientsocket=accept(serversocket,(struct sockaddr*)&clientaddr,&addr_size);
            if(clientsocket<0)
            {
	            perror("error in accepting connection\n");
	            exit(1);
            }
    
            else
            {
	            printf("Sending\n");
	           char buffer2[BUFFER_SIZE] = {"ii"};
                // sleep_time.tv_nsec = 1000000000 / frequency;
                 if(bytes_sent_2<TARGET_MBPS_2)
                {
                uint64_t period = (uint64_t)(1000000000/frequency);
	            trig_time.tv_sec = period/1000000000;
	            trig_time.tv_nsec = period%1000000000;

                
                
	                bytes_sent_2=send(clientsocket,buffer2,BUFFER_SIZE,0);
	                {
	                   perror("Error in sending\n");
	                }	
                    nanosleep(&trig_time, NULL);
                    total_bytes_sent_2+=bytes_sent_2;
    
            }  
             printf("Sent %ld bytes at %ld Mbps.\n", total_bytes_sent_2, TARGET_MBPS_2);

        }
        // else
        // {
        //     printf("no server\n");
        // }
        
          
        }
    // } 
}

int main()
{
    int ports[MAX_PORTS] = {6321, 6322};

    // Create multiple threads to listen on different ports
    pthread_t server_threads[MAX_PORTS];

    for (int i = 0; i < MAX_PORTS; i++) {
        pthread_create(&server_threads[i], NULL, (void*)server, (void*)&ports[i]);
    }

    // Wait for all server threads to finish
    for (int i = 0; i < MAX_PORTS; i++) {
        pthread_join(server_threads[i], NULL);
    }
    return 0;
}