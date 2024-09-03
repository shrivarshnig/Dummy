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


  printf("client\n");
    socklen_t addr_size;
       struct sockaddr_in ats_clientaddress;
       int sockfd;

  
   
    addr_size=sizeof(ats_clientaddress); 

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
    ats_clientaddress.sin_port = htons(PORT);

    /*Connect to the client*/
    if (connect(sockfd, (struct sockaddr *)&ats_clientaddress,sizeof(ats_clientaddress)) == -1) 
    {
        perror("Connection failed");
        exit(1);
    }
    printf("connected successfully\n");

    server_send_t receive;

    printf("got successfully\n");

    int num_bytes1=recv(sockfd,(void*)&receive,sizeof(server_send_t),0);

        if(num_bytes1<=0)
        {
            perror("Error in receiving\n");

            exit(1);
            
        }

        printf("the value is %d\n",receive.send_command);

}