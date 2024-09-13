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
typedef struct {
    uint8_t send_command;
    
}server_send_t;

long get_current_time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void log_time(const char* action, int port, long timestamp) {
    FILE *log_file = fopen("server_log.txt", "a");
    if (log_file != NULL) {
        fprintf(log_file, "[%s] Port: %d, Timestamp: %ld ms\n", action, port, timestamp);
        fclose(log_file);
    }
}

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
            int frequency = 1;
            clientsocket=accept(serversocket,(struct sockaddr*)&clientaddr,&addr_size);
            if(clientsocket<0)
            {
	            perror("error in accepting connection\n");
	            exit(1);
            }

            else
            {
	            printf("Sending\n");
	            server_send_t sending={.send_command=1};
                // sleep_time.tv_sec = 1;

                uint64_t period = (uint64_t)(1000000000/frequency);
	            trig_time.tv_sec = period/1000000000;
	            trig_time.tv_nsec = period%1000000000;

                for(int i = 0; i < 10 ; i++)
                {
                    log_time("Sent", port, get_current_time_ms());
	                if(send(clientsocket,(void *)&sending,sizeof(sending),0)==-1)
	                {
	                   perror("Error in sending\n");
	                }	
                    // nanosleep(&sleep_time, NULL);
                    if(nanosleep(&trig_time, NULL)==-1){
                        perror("Error in nanosleep\n");
                        exit(1);
                    }
            
                    // sleep(1);
	                printf("send_command is:%d\n",sending.send_command);

                }
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
	            struct timeval St;   
	            gettimeofday(&St,NULL);
	            server_send_t sending={.send_command=2};
                // sleep_time.tv_nsec = 1000000000 / frequency;

                uint64_t period = (uint64_t)(1000000000/frequency);
	            trig_time.tv_sec = period/1000000000;
	            trig_time.tv_nsec = period%1000000000;

                for(int i = 0; i < 10 ; i++)
                {
                    log_time("Sent", port, get_current_time_ms());
	                if(send(clientsocket,(void *)&sending,sizeof(sending),0)==-1)
	                {
	                   perror("Error in sending\n");
	                }	
                    nanosleep(&trig_time, NULL);
	                printf("send_command is:%d\n",sending.send_command);
    
                }
            }  
        }
        // else
        // {
        //     printf("no server\n");
        // }
        
        else if(port == 6323)
        {
            int frequency = 100;
            clientsocket=accept(serversocket,(struct sockaddr*)&clientaddr,&addr_size);
            if(clientsocket<0)
            {
	            perror("error in accepting connection\n");
	            exit(1);
            }
    
            else
            {
                log_time("Sent", port, get_current_time_ms());
	            printf("Sending\n");
	            server_send_t sending={.send_command=3};
                // sleep_time.tv_nsec = 1000000000 / frequency;

                uint64_t period = (uint64_t)(1000000000/frequency);
	            trig_time.tv_sec = period/1000000000;
	            trig_time.tv_nsec = period%1000000000;

                for(int i = 0; i < 10 ; i++)
                {
                
	                if(send(clientsocket,(void *)&sending,sizeof(sending),0)==-1)
	                {
	                   perror("Error in sending\n");
	                }	
                    nanosleep(&trig_time, NULL);
	                printf("send_command is:%d\n",sending.send_command);
    
                }
            }  
        }

        
        else if(port == 6324)
        {
            int frequency = 1000;
            clientsocket=accept(serversocket,(struct sockaddr*)&clientaddr,&addr_size);
            if(clientsocket<0)
            {
	            perror("error in accepting connection\n");
	            exit(1);
            }
    
            else
            {
	            printf("Sending\n");
	            server_send_t sending={.send_command=4};
                // sleep_time.tv_nsec = 1000000000 / frequency;

                uint64_t period = (uint64_t)(1000000000/frequency);
	            trig_time.tv_sec = period/1000000000;
	            trig_time.tv_nsec = period%1000000000;

                for(int i = 0; i < 10 ; i++)
                {
                
	                if(send(clientsocket,(void *)&sending,sizeof(sending),0)==-1)
	                {
	                   perror("Error in sending\n");
	                }	
                    nanosleep(&trig_time, NULL);
	                printf("send_command is:%d\n",sending.send_command);
    
                }
            }  
        }
        if(port == 6325)
        {
            int frequency = 2000;
            clientsocket=accept(serversocket,(struct sockaddr*)&clientaddr,&addr_size);
            if(clientsocket<0)
            {
	            perror("error in accepting connection\n");
	            exit(1);
            }
    
            else
            {
	            printf("Sending\n");
	            server_send_t sending={.send_command=5};
                // sleep_time.tv_nsec = 1000000000 / frequency;

                uint64_t period = (uint64_t)(1000000000/frequency);
	            trig_time.tv_sec = period/1000000000;
	            trig_time.tv_nsec = period%1000000000;

                for(int i = 0; i < 10 ; i++)
                {
                
	                if(send(clientsocket,(void *)&sending,sizeof(sending),0)==-1)
	                {
	                   perror("Error in sending\n");
	                }	
                    nanosleep(&trig_time, NULL);
	                printf("send_command is:%d\n",sending.send_command);
    
                }
            }  
        }
    // } 
}  

int main()
{
    int ports[MAX_PORTS] = {6321, 6322, 6323, 6324, 6325};

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