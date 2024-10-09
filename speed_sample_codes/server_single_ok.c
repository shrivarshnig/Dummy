#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/time.h>
#include <time.h>
#include <pthread.h>

// #define PORT  10069
#define IP ("127.0.0.1")
#define BUFFER_SIZE 1024
#define MAX_PORTS 1
#define TARGET_RATE_MBPS_1 1024
#define TARGET_RATE_MBPS_2 10240
#define TARGET_RATE_MBPS_3 25600
#define TARGET_RATE_MBPS_4 62464
#define TARGET_RATE_MBPS_5 102400
#define TARGET_RATE_MBPS_6 128000
#define TARGET_RATE_MBPS_7 256000
#define TARGET_RATE_MBPS_8 512000
#define TARGET_RATE_MBPS_9 1024000
#define TARGET_RATE_MBPS_10 2048000
#define TARGET_RATE_MBPS_11 5120000
#define TARGET_RATE_MBPS_12 10240000
#define TARGET_RATE_MBPS_13 20480000

typedef struct {
    uint8_t send_command;
    
}server_send_t;

void PORT1();
void PORT2();
void PORT3();
void PORT4();
void PORT5();
void PORT6();
void PORT7();
void PORT8();
void PORT9();
void PORT10();
void PORT11();
void PORT12();



void* server(void* arg);

static int ports[MAX_PORTS] ={6322};
// ,6322,6323,6324,6325,6326,6327,6328,6329,6330,6331,6332,6333};

// {6332};
// static int serversocket,clientsocket;  
// static struct sockaddr_in servaddr,clientaddr;
static int serversocket[MAX_PORTS],clientsocket;  
static struct sockaddr_in servaddr[MAX_PORTS],clientaddr[MAX_PORTS];
static int port;
static struct timespec trig_time;
static socklen_t addr_size;
static int i;
static int e,n; 

int main()
{



for (i=0;i<MAX_PORTS;i++)
{
    serversocket[i]=socket(AF_INET,SOCK_STREAM,0);
    if(serversocket == -1)
    {
       printf("socket creation failed\n");
       exit(1);
    }
    printf("Socket successfully for client[-%d] \n",i);

        //assign IP Address

    servaddr[i].sin_family=AF_INET; 
    servaddr[i].sin_port = htons(ports[i]);
    servaddr[i].sin_addr.s_addr=inet_addr(IP);

    printf("Before Binding\n");
    int opt = 1;
    if (setsockopt(serversocket[i], SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    e=bind(serversocket[i],(struct sockaddr*)&servaddr[i],sizeof(servaddr[i]));
    if(e<0)
    {
	    perror("Error in binding123\n");
	    exit(1);
    }
    printf("Binding Successful for client[-%d] \n",i);
    n=listen(serversocket[i],10);
    if(n<0)
    {
	     perror("Failed to listen for connections\n");
	     exit(1);
    }
        printf("Listening for client[-%d] \n",i);
}
while(1)
{
    for (i=0;i<MAX_PORTS;i++)
    {
        printf("accepting in");
        addr_size=sizeof(servaddr[0]); 
        clientsocket=accept(serversocket[i],(struct sockaddr*)&clientaddr[i],&addr_size);
        if(clientsocket<0)
        {
            perror("error in accepting connection\n");
            exit(1);
        }
   printf("Connection accepted by the  client[-%d]\n",i);
       

    // PORT1();
    PORT2(); 
    // PORT3();
    // PORT4();
    // PORT5();
    // PORT6();
    // PORT7();
    // PORT8();
    // PORT9();
    // PORT10();
    // PORT11();
    // PORT12();
    // PORT13();

}
    
  }  
}      
void PORT1()
{
    if(ports[i] == 6321)
    {            
        int frequency = 1;
        char buffer_1[BUFFER_SIZE];  // Buffer to hold data
        long target_rate_bps_1 = 1024/8;  // Convert target rate to bytes per second
        long total_bytes_received_1 = 0;
        FILE *fd=fopen("ports_1.csv","w");
        if(fd==NULL)
        {
            printf("empty file\n");
        }
        FILE *fd1=fopen("ports.csv","w");

        while (total_bytes_received_1 < target_rate_bps_1) 
        {                // sleep_time.tv_sec = 1;

            uint64_t period = (uint64_t)(1000000000/frequency);
            trig_time.tv_sec = period/1000000000;
            trig_time.tv_nsec = period%1000000000;

        
            ssize_t bytes_received_1 =recv(clientsocket, buffer_1,BUFFER_SIZE, 0);
            if(bytes_received_1<0)
            {
                perror("Error in sending-1\n");
            }	
        
            if(nanosleep(&trig_time, NULL)==-1){
                perror("Error in nanosleep\n");
                exit(1);
            }
            total_bytes_received_1 += bytes_received_1;

            fprintf(fd,"port-1 %d Received %ld bytes. Total received: %ld bytes\n",ports[i], bytes_received_1, total_bytes_received_1);
            fflush(fd);                  
        }  
        printf("Received a total of %ld bytes at %ld Mbps.\n", total_bytes_received_1 , TARGET_RATE_MBPS_1);

    }
}
void PORT2()
{
    if(ports[i] == 6322)
        {
            printf("port-2\n");
            int frequency = 10;
            char buffer_2[BUFFER_SIZE];  // Buffer to hold data
            long target_rate_bps_2 = 10240/8;  // Convert target rate to bytes per second
            long total_bytes_sent_2 = 0;
            FILE *fd=fopen("ports_2.csv","w");
            if(fd==NULL)
            {
                printf("empty file\n");
            }
            while (total_bytes_sent_2 < target_rate_bps_2) 
            {              
                uint64_t period = (uint64_t)(1000000000/frequency);
	            trig_time.tv_sec = period/1000000000;
	            trig_time.tv_nsec = period%1000000000;
                ssize_t bytes_received_2=recv(clientsocket, buffer_2,BUFFER_SIZE, 0);
                if(bytes_received_2<0)
                {
                    perror("Error in sending\n");
                }	
                nanosleep(&trig_time, NULL);
                total_bytes_sent_2 += bytes_received_2;
                fprintf(fd,"port2-%d Received %ld bytes. Total received: %ld bytes\n",ports[i], bytes_received_2, total_bytes_sent_2);
                fflush(fd);
            }
            printf("Received a total of %ld bytes at %ld Mbps.\n", total_bytes_sent_2, TARGET_RATE_MBPS_2);

        }
 }
 void PORT3()
 {

 

         if(ports[i] == 6323)
        {
            printf("port-2\n");
            int frequency = 25;
            char buffer_3[BUFFER_SIZE]={"l"};  // Buffer to hold data
            long target_rate_bps_3 = 25600/8;  // Convert target rate to bytes per second
            long total_bytes_sent_3 = 0;
                        
                while (total_bytes_sent_3 < target_rate_bps_3) {                // sleep_time.tv_sec = 1;

                // sleep_time.tv_nsec = 1000000000 / frequency;

                uint64_t period = (uint64_t)(1000000000/frequency);
	            trig_time.tv_sec = period/1000000000;
	            trig_time.tv_nsec = period%1000000000;

                
	             ssize_t bytes_sent_3=send(clientsocket, buffer_3,BUFFER_SIZE, 0);
                 if(bytes_sent_3<0)
	                {
	                   perror("Error in sending\n");
	                }	
                    nanosleep(&trig_time, NULL);
                        total_bytes_sent_3 += bytes_sent_3;

                                printf("%s",buffer_3);        
            }
                        printf("Sent for port 2 %ld bytes at %ld Mbps.\n", total_bytes_sent_3, TARGET_RATE_MBPS_3);

        }
 }
 void PORT4()
 {
         if(ports[i] == 6324)
        {
            printf("port-2\n");
            int frequency = 61;
            char buffer_4[BUFFER_SIZE]={"m"};  // Buffer to hold data
            long target_rate_bps_4 = 62464/8;  // Convert target rate to bytes per second
            long total_bytes_sent_4 = 0;
                        
                while (total_bytes_sent_4 < target_rate_bps_4) {                // sleep_time.tv_sec = 1;

                // sleep_time.tv_nsec = 1000000000 / frequency;

                uint64_t period = (uint64_t)(1000000000/frequency);
	            trig_time.tv_sec = period/1000000000;
	            trig_time.tv_nsec = period%1000000000;

                
	             ssize_t bytes_sent_4=send(clientsocket, buffer_4,BUFFER_SIZE, 0);
                 if(bytes_sent_4<0)
	                {
	                   perror("Error in sending\n");
	                }	
                    nanosleep(&trig_time, NULL);
                        total_bytes_sent_4 += bytes_sent_4;

                                printf("%s",buffer_4);        
            }
                        printf("Sent for port 2 %ld bytes at %ld Mbps.\n", total_bytes_sent_4, TARGET_RATE_MBPS_4);

        }
 }
 void PORT5()
 {
        if(ports[i] == 6325)
        {
            printf("port-2\n");
            int frequency = 100;
            char buffer_5[BUFFER_SIZE]={"n"};  // Buffer to hold data
            long target_rate_bps_5 = 102400/8;  // Convert target rate to bytes per second
            long total_bytes_sent_5 = 0;
                        
                while (total_bytes_sent_5 < target_rate_bps_5) {                // sleep_time.tv_sec = 1;

                // sleep_time.tv_nsec = 1000000000 / frequency;

                uint64_t period = (uint64_t)(1000000000/frequency);
	            trig_time.tv_sec = period/1000000000;
	            trig_time.tv_nsec = period%1000000000;

                
	             ssize_t bytes_sent_5=send(clientsocket, buffer_5,BUFFER_SIZE, 0);
                 if(bytes_sent_5<0)
	                {
	                   perror("Error in sending\n");
	                }	
                    nanosleep(&trig_time, NULL);
                        total_bytes_sent_5 += bytes_sent_5;

                                printf("%s",buffer_5);        
            }
                        printf("Sent for port 2 %ld bytes at %ld Mbps.\n", total_bytes_sent_5, TARGET_RATE_MBPS_5);

        }
 }
 void PORT6()
 {
        if(ports[i] == 6326)
        {
            printf("port-2\n");
            int frequency = 125;
            char buffer_6[BUFFER_SIZE]={"o"};  // Buffer to hold data
            long target_rate_bps_6 = 128000/8;  // Convert target rate to bytes per second
            long total_bytes_sent_6 = 0;
                        
                while (total_bytes_sent_6 < target_rate_bps_6) {                // sleep_time.tv_sec = 1;

                // sleep_time.tv_nsec = 1000000000 / frequency;

                uint64_t period = (uint64_t)(1000000000/frequency);
	            trig_time.tv_sec = period/1000000000;
	            trig_time.tv_nsec = period%1000000000;

                
	             ssize_t bytes_sent_6=send(clientsocket, buffer_6,BUFFER_SIZE, 0);
                 if(bytes_sent_6<0)
	                {
	                   perror("Error in sending\n");
	                }	
                    nanosleep(&trig_time, NULL);
                        total_bytes_sent_6 += bytes_sent_6;

                                printf("%s",buffer_6);        
            }
                        printf("Sent for port 2 %ld bytes at %ld Mbps.\n", total_bytes_sent_6, TARGET_RATE_MBPS_6);

        }
 }
 void PORT7()
 {
        if(ports[i] == 6327)
        {
            printf("port-2\n");
            int frequency = 250;
            char buffer_7[BUFFER_SIZE]={"o"};  // Buffer to hold data
            long target_rate_bps_7 = 256000/8;  // Convert target rate to bytes per second
            long total_bytes_sent_7= 0;
                        
                while (total_bytes_sent_7 < target_rate_bps_7) {                // sleep_time.tv_sec = 1;

                // sleep_time.tv_nsec = 1000000000 / frequency;

                uint64_t period = (uint64_t)(1000000000/frequency);
	            trig_time.tv_sec = period/1000000000;
	            trig_time.tv_nsec = period%1000000000;

                
	             ssize_t bytes_sent_7=send(clientsocket, buffer_7,BUFFER_SIZE, 0);
                 if(bytes_sent_7<0)
	                {
	                   perror("Error in sending\n");
	                }	
                    nanosleep(&trig_time, NULL);
                        total_bytes_sent_7 += bytes_sent_7;

                                printf("%s",buffer_7);        
            }
                        printf("Sent for port 2 %ld bytes at %ld Mbps.\n", total_bytes_sent_7, TARGET_RATE_MBPS_7);

        }
 }
 void PORT8()
 {
        if(ports[i] == 6328)
        {
            printf("port-2\n");
            int frequency = 500;
            char buffer_8[BUFFER_SIZE]={"o"};  // Buffer to hold data
            long target_rate_bps_8 = 512000/8;  // Convert target rate to bytes per second
            long total_bytes_sent_8= 0;
                        
                while (total_bytes_sent_8 < target_rate_bps_8) {                // sleep_time.tv_sec = 1;

                // sleep_time.tv_nsec = 1000000000 / frequency;

                uint64_t period = (uint64_t)(1000000000/frequency);
	            trig_time.tv_sec = period/1000000000;
	            trig_time.tv_nsec = period%1000000000;

                
	             ssize_t bytes_sent_8=send(clientsocket, buffer_8,BUFFER_SIZE, 0);
                 if(bytes_sent_8<0)
	                {
	                   perror("Error in sending\n");
	                }	
                    nanosleep(&trig_time, NULL);
                        total_bytes_sent_8 += bytes_sent_8;

                                printf("%s",buffer_8);        
            }
                        printf("Sent for port 2 %ld bytes at %ld Mbps.\n", total_bytes_sent_8, TARGET_RATE_MBPS_8);

        }
 }
 void PORT9()
 {
        if(ports[i] == 6329)
        {
            printf("port-2\n");
            int frequency = 1000;
            char buffer_9[BUFFER_SIZE]={"o"};  // Buffer to hold data
            long target_rate_bps_9 = 1024000/8;  // Convert target rate to bytes per second
            long total_bytes_sent_9= 0;
                        
                while (total_bytes_sent_9 < target_rate_bps_9) {                // sleep_time.tv_sec = 1;

                // sleep_time.tv_nsec = 1000000000 / frequency;

                uint64_t period = (uint64_t)(1000000000/frequency);
	            trig_time.tv_sec = period/1000000000;
	            trig_time.tv_nsec = period%1000000000;

                
	             ssize_t bytes_sent_9=send(clientsocket, buffer_9,BUFFER_SIZE, 0);
                 if(bytes_sent_9<0)
	                {
	                   perror("Error in sending\n");
	                }	
                    nanosleep(&trig_time, NULL);
                        total_bytes_sent_9 += bytes_sent_9;

                                printf("%s",buffer_9);        
            }
                        printf("Sent for port 2 %ld bytes at %ld Mbps.\n", total_bytes_sent_9, TARGET_RATE_MBPS_9);

        }
 }
 void PORT10()
 {
        if(ports[i] == 6330)
        {
            printf("port-2\n");
            int frequency = 2000;
            char buffer_10[BUFFER_SIZE]={"o"};  // Buffer to hold data
            long target_rate_bps_10= 2048000/8;  // Convert target rate to bytes per second
            long total_bytes_sent_10= 0;
                        
                while (total_bytes_sent_10 < target_rate_bps_10) {                // sleep_time.tv_sec = 1;

                uint64_t period = (uint64_t)(1000000000/frequency);
	            trig_time.tv_sec = period/1000000000;
	            trig_time.tv_nsec = period%1000000000;

                
	             ssize_t bytes_sent_10=send(clientsocket, buffer_10,BUFFER_SIZE, 0);
                 if(bytes_sent_10<0)
	                {
	                   perror("Error in sending\n");
	                }	
                    nanosleep(&trig_time, NULL);
                        total_bytes_sent_10 += bytes_sent_10;

                                printf("%s",buffer_10);        
            }
                        printf("Sent for port 2 %ld bytes at %ld Mbps.\n", total_bytes_sent_10, TARGET_RATE_MBPS_10);

        }
 }
 void PORT11()
 {

    
        if(ports[i] == 6331)
        {
            printf("port-2\n");
            int frequency = 5000;
            char buffer_11[BUFFER_SIZE]={"o"};  // Buffer to hold data
            long long target_rate_bps_11= 5120000/8;  // Convert target rate to bytes per second
            long long total_bytes_sent_11= 0;
                        
                while (total_bytes_sent_11 < target_rate_bps_11) {                // sleep_time.tv_sec = 1;

                uint64_t period = (uint64_t)(1000000000/frequency);
	            trig_time.tv_sec = period/1000000000;
	            trig_time.tv_nsec = period%1000000000;

                
	             ssize_t bytes_sent_12=send(clientsocket, buffer_11,BUFFER_SIZE, 0);
                 if(bytes_sent_12<0)
	                {
	                   perror("Error in sending\n");
	                }	
                    nanosleep(&trig_time, NULL);
                        total_bytes_sent_11 += bytes_sent_12;

                                printf("%s\n",buffer_11);        
            }
                        printf("Sent for port 2 %ld bytes at %ld Mbps.\n", total_bytes_sent_11, TARGET_RATE_MBPS_12);

        }
 }
 void PORT12()
 {

    
        if(ports[i] == 6332)
        {
            printf("port-2\n");
            int frequency = 10000;
            char buffer_12[BUFFER_SIZE]={"o"};  // Buffer to hold data
            long long target_rate_bps_12= 10240000/8;  // Convert target rate to bytes per second
            long long total_bytes_sent_12= 0;
                        
                while (total_bytes_sent_12 < target_rate_bps_12) {                // sleep_time.tv_sec = 1;

                uint64_t period = (uint64_t)(1000000000/frequency);
	            trig_time.tv_sec = period/1000000000;
	            trig_time.tv_nsec = period%1000000000;

                
	             ssize_t bytes_sent_12=send(clientsocket, buffer_12,BUFFER_SIZE, 0);
                 if(bytes_sent_12<0)
	                {
	                   perror("Error in sending\n");
	                }	
                    nanosleep(&trig_time, NULL);
                        total_bytes_sent_12 += bytes_sent_12;

                                printf("%s\n",buffer_12);        
            }
                        printf("Sent for port 2 %ld bytes at %ld Mbps.\n", total_bytes_sent_12, TARGET_RATE_MBPS_12);

        }
 }
 void PORT13()
 {

    
        if(ports[i] == 6333)
        {
            printf("port-2\n");
            int frequency = 20000;
            char buffer_13[BUFFER_SIZE]={"o"};  // Buffer to hold data
            long long target_rate_bps_13= 20480000/8;  // Convert target rate to bytes per second
            long long total_bytes_sent_13= 0;
                        
                while (total_bytes_sent_13 < target_rate_bps_13) {                // sleep_time.tv_sec = 1;

                uint64_t period = (uint64_t)(1000000000/frequency);
	            trig_time.tv_sec = period/1000000000;
	            trig_time.tv_nsec = period%1000000000;

                
	             ssize_t bytes_sent_12=send(clientsocket, buffer_13,BUFFER_SIZE, 0);
                 if(bytes_sent_12<0)
	                {
	                   perror("Error in sending\n");
	                }	
                    nanosleep(&trig_time, NULL);
                        total_bytes_sent_13 += bytes_sent_12;

                                printf("%s\n",buffer_13);        
            }
                        printf("Sent for port 2 %ld bytes at %ld Mbps.\n", total_bytes_sent_13, TARGET_RATE_MBPS_12);

        }
 }