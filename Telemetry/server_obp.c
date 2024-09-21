#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<unistd.h>

#include <zds_p2p_init.h>
#include <zds_cnc_configuration.h>
#include <zds_cnc_init.h>
#include <zds_p2p_send.h>
#include <zds_p2p_receive.h>
#include <zds_p2p.h>
#include <zds_cnc.h>

#define MAX_VALUE (0xFFFF)
#define MID_VALUE (0x8000)
#define MIN_VALUE (0x0000)
#define PORT  12345
#define SERVER_IP "127.0.0.1"
typedef struct {
    uint32_t send_command;

}server_send_t;

s_configuration configuration; / For processing initialization */
s_p2p_communication p2p_communication_p; / For processing initialization */
s_configuration configuration; / For processing initialization */
s_p2p_communication p2p_communication_p; / For processing initialization */
uint16_t ui16_current_max_value = 0;
//float alpha; /* Alpha coefficient as float */
//float current_average; /* Float storing current value of the average */
//int current_average_initialized = 0; /* Boolean stating whether average is initialized */
/* Local functions */
void handle_acquisition_0(uint16_t id, uint64_t timestamp, uint16_t length,
uint16_t *value);
//zds_p2p_set_handler(p2p_communication_p, 0, handle_acquisition_0);
//zds_p2p_set_handler(p2p_communication_p, 0, handle_acquisition_0);


/* Main program */
int main (int argc, char *argv[])
{
/* zds CnC Initialization*/
if (zds_cnc_initialize(&configuration)!=0)
{
syslog(LOG_ERR, "Cannot initialize zds cnc\n");
exit(1);
}
/* zds P2P Initialization*/
if (zds_p2p_initialize(configuration, ZDS_USE_HANDLER, &p2p_communication_p ) != 0)
{
syslog(LOG_ERR, "Cannot initialize zds p2p\n");
}
/* Parameters retrieval */
server_send_t sends;
/* copy of alpha value as double into double_alpha */
zds_cnc_configuration_get_parameter(configuration, 0,&sends);
/* conversion into float */

/* Endless loop */
/* MODIFY ENDLESS LOOP IF YOU NEED TO OUPUT DATA WITHOUT THE INPUT HANDLERS DEFINED
ABOVE */
while(1)
{
     usleep(1000*1000);
}
return 0;

}

void handle_acquisition_0(uint16_t id, uint64_t timestamp, uint16_t length, uint16_t
*value)
{
    server();
    zds_p2p_send_acquisition_synchronous(p2p_communication_p,

    0 /* output order 1 */,
    timestamp /* same timestamp as input */,
    &ui16_current_max_value, /* payload as array of uint16_t */
    1,
    1); /* length of the array */
}
int server()
{
    int a=5,b=10;
    int c=a+b;
    printf("the addition is %d\n",c);
    printf("server\n");
        int e;

        int serversocket,clientsocket;
        struct sockaddr_in servaddr ,clientaddr;
        socklen_t addr_size;

        addr_size=sizeof(clientaddr);
       //to start the socket


        //socket creation
       serversocket=socket(AF_INET,SOCK_STREAM,0);
       if(serversocket == -1)
       {
          printf("socket creation failed\n");

          exit(1);
       }
       printf("Socket successfully created\n");

       //assign IP Address

       servaddr.sin_family=AF_INET;
       servaddr.sin_port = htons(PORT );
       servaddr.sin_addr.s_addr=inet_addr(SERVER_IP);
       printf("assigned IP_ADDRESS\n");
       printf("before binding\n");
       int optval = 1;
       setsockopt(serversocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&optval, sizeof(optval));
       printf("Before Binding_1\n");
       //bind the port number and IP_ADDRESS
       e=bind(serversocket,(struct sockaddr*)&servaddr,sizeof(servaddr));
       if(e<0)
       {
          perror("Error in binding123\n");

          exit(1);
       }
       printf("Binding Successful\n");

       //Listening to the clients
       if (listen(serversocket, 1)<0)
       {
          printf("failed to listen\n");

          exit(1);
       }
       printf("Listening\n");
       printf("Waiting for incoming connections...\n");
       //Allow the clients in blocking mode
       //it will wait for the client to accept
//       if (ioctlsocket(serversocket, FIONBIO, &mode) != 0)
//       {
//           printf("Failed to set non-blocking mode\n");
//           closesocket(serversocket);
//           WSACleanup();
//           return 1;
//       }
       printf("server is listening on the port %d\n",PORT );
       printf("accepts\n");
       // accept the client to connect
       clientsocket = accept(serversocket, (struct sockaddr*)&clientaddr, (socklen_t*)&addr_size);
       printf("the value of the socket is %d\n",clientsocket);
       if (clientsocket < 0)
       {

           printf("the value of the return value is %d\n",clientsocket);

        }
        printf("Accepted a connection\n");
        server_send_t sending={.send_command=10};

        //sending the command to the client
       if(send(clientsocket,(void *)&sending,sizeof(sending),0)==-1)
        {
            perror("Error in sending\n");
        }
       printf("send_command is:%d\n",sending.send_command);
       return 0;


}
