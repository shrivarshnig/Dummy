 #include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/time.h>

#define PORT  10069
#define IP ("127.0.0.1")
typedef struct {
    uint8_t send_command;
    
}server_send_t;




 int main()
 {
 
 
 int e,n; 
   uint8_t hold;
   int serversocket,clientsocket;  
   struct sockaddr_in servaddr,clientaddr;
   socklen_t addr_size;
      
   serversocket=socket(AF_INET,SOCK_STREAM,0);
   if(serversocket == -1)
   {
      printf("socket creation failed\n");
   }
   printf("Socket successfully created\n");
       //assign IP Address
       
   servaddr.sin_family=AF_INET; 
   servaddr.sin_port = htons(PORT);
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
   printf("Listening\n");
   while(1)
   {
   addr_size=sizeof(clientaddr); 
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
	server_send_t sending={.send_command=10};
	if(send(clientsocket,(void *)&sending,sizeof(sending),0)==-1)
	{
	   perror("Error in sending\n");
	}	
	printf("send_command is:%d\n",sending.send_command);

   }
   }
   return 0;
 }