#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int sockfd = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = "Client_1 running..";

    if(argc <3)
    {
        printf("command: ./client <server address> <port number>\n");
        exit(1);
    }

    //create client socket
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) <0)
    {
        perror("sock()");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));

    //Convert IP from text to binanry
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <=0)
    {
        printf("Invalid address/ Address not support \n");
        return -1;
    }

    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <0)
    {
       printf("Connect failed");
        return -1;
    }
    send(sockfd, buffer, strlen(buffer), 0);
    while (1){
        memset(&buffer, 0, sizeof(buffer));
        fgets(buffer, 1024, stdin);
        send(sockfd, buffer, strlen(buffer), 0);
    }

    return 0;
}