#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
// #include<windows.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/ioctl.h>
// #include <winsock2.h>
// #include <ws2tcpip.h>
#define PORT  12345
#define SERVER_IP "127.0.0.1"
typedef struct {
    int send_command;

}server_send_t;

 int set_blocking(int fd);
 int main()
 {
     int a=8,b=10;
         int c=b*a;
         printf("%d\n",c);

printf("server\n");
 int e,n;
   int serversocket,clientsocket;
    int flags = 1;
 struct sockaddr_in servaddr ,clientaddr;
  socklen_t addr_size;
  addr_size=sizeof(clientaddr);


   serversocket=socket(AF_INET,SOCK_STREAM,0);
   if(serversocket == -1)
   {
      printf("socket creation failed\n");
      exit(1);
   }
   printf("Socket successfully created\n");
       //assign IP Address
   if (ioctl(serversocket, FIONBIO, &flags) == -1) {
        perror("ioctl failed");
      exit(1);
    }
   servaddr.sin_family=AF_INET;
   servaddr.sin_port = htons(PORT);
   servaddr.sin_addr.s_addr=inet_addr(SERVER_IP);
   printf("assigned IP_ADDRESS\n");
   printf("before binding\n");
   int optval = 1;
    setsockopt(serversocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&optval, sizeof(optval));
  printf("Before Binding_1\n");
   e=bind(serversocket,(struct sockaddr*)&servaddr,sizeof(servaddr));
   if(e<0)
   {
    perror("Error in binding123\n");
    exit(1);
}
  printf("Binding Successful\n");

  if (listen(serversocket, 1) <0)
   {
       printf("error\n");
       exit(1);
 }
 printf("Waiting for incoming connections...\n");
   printf("Listening\n");
   if (set_blocking(serversocket) == -1) {
        perror("Failed to set server socket to non-blocking mode");
        exit(1);
    }
    
  while (1) {
           clientsocket = accept(serversocket, (struct sockaddr*)&clientaddr, (socklen_t*)&addr_size);

           if (clientsocket < 0) {
              
               printf("error\n");
               }
               printf("accepted\n");
           
  
     server_send_t sending={.send_command=10};
   if(send(clientsocket,(void *)&sending,sizeof(sending),0)==-1)
   {
      perror("Error in sending\n");
   }
   printf("send_command is:%d\n",sending.send_command);
  }
        
//   while (1) {
////       Sleep(100);
//   clientsocket=accept(serversocket,(struct sockaddr*)&clientaddr,&addr_size);
//   if(clientsocket<0)
//   {
//    perror("error in accepting connection\n");
//    exit(1);
//   }
//
//}
//   printf("accepted\n");
//   else
//   {
//    printf("Sending\n");
//    server_send_t sending={.send_command=10};
//    if(send(clientsocket,(void *)&sending,sizeof(sending),0)==-1)
//    {
//       perror("Error in sending\n");
//    }
//    printf("send_command is:%d\n",sending.send_command);
//
//   }
//   }
   return 0;
 }
 int set_blocking(int fd) {
    // Get the current file descriptor flags
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl F_GETFL");
        return -1;
    }

    // Clear the O_NONBLOCK flag to enable blocking mode
    flags &= ~O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) == -1) {
        perror("fcntl F_SETFL");
        return -1;
    }
    return 0;
}