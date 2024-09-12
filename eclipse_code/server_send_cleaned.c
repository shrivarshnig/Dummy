#include<stdint.h>
#include<stdio.h>
#include<fcntl.h>
#include<windows.h>
#include<unistd.h>
#include <winsock2.h>
#include <ws2tcpip.h>


#define PORT  10069
#define SERVER_IP "127.0.0.1"

typedef struct {
    int send_command;

}server_send_t;


 int main()
 {

    printf("server\n");
    int e;
    WSADATA wsa;
    int serversocket,clientsocket;
    struct sockaddr_in servaddr ,clientaddr;
    socklen_t addr_size;
    u_long mode = 0;
    addr_size=sizeof(clientaddr);
   //to start the socket

    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0)
    {
       printf("Failed. Error Code : %d", WSAGetLastError());
       WSACleanup();
       return 1;
    }

    //socket creation
   serversocket=socket(AF_INET,SOCK_STREAM,0);
   if(serversocket == -1)
   {
      printf("socket creation failed\n");
      WSACleanup();
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
      WSACleanup();
      exit(1);
   }
   printf("Binding Successful\n");

   //Listening to the clients
   if (listen(serversocket, 1) == SOCKET_ERROR)
   {
       printf("Listen failed with error code : %d\n", WSAGetLastError());
       closesocket(serversocket);
       WSACleanup();
       return 1;
   }
   printf("Listening\n");
   printf("Waiting for incoming connections...\n");
   //Allow the clients in blocking mode
   //it will wait for the client to accept
   if (ioctlsocket(serversocket, FIONBIO, &mode) != 0)
   {
       printf("Failed to set non-blocking mode\n");
       closesocket(serversocket);
       WSACleanup();
       return 1;
   }
   printf("server is listening on the port %d\n",PORT );
   printf("accepts\n");
   // accept the client to connect
   clientsocket = accept(serversocket, (struct sockaddr*)&clientaddr, (socklen_t*)&addr_size);
   printf("the value of the socket is %d\n",clientsocket);
   if (clientsocket < 0)
   {
       int error = WSAGetLastError();
       printf("Error is %d\n",error);
       if (error == WSAEWOULDBLOCK)
       {
           printf("error\n");
           exit(1);

        }
       else
       {
                   // Handle other errors
            printf("Error in accepting connection. Error Code : %d\n", error);
            WSACleanup();
            return 1;

        }
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

