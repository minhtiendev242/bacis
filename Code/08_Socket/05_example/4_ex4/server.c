#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/select.h>
#include <arpa/inet.h>



#define MAX_CLIENTS 10

int main(int argc, char *argv[])
{
    int server_fd, client_fd[MAX_CLIENTS], max_clients = MAX_CLIENTS, activity, max_fd;
    struct sockaddr_in address;
    int addrLen = sizeof(address);
    fd_set readfds;  // khoi tao danh sach doc cho ham select
    char buffer[1024];

    //create porter on cmd
    if(argc<2)
    {
        printf("No port provide\ncommand: ./server <port number>\n");
        exit(EXIT_FAILURE);
    }

    //initialize all client socket to 0
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        client_fd[i]=0;
    }

    //create socket
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("create socket()");
        exit(EXIT_FAILURE);
    }

    //set server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(atoi(argv[1])); 

    //bind
    if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind()");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    //listen
    if(listen(server_fd, MAX_CLIENTS) <0)
    {
        perror("listen()");
        exit(EXIT_FAILURE);
    }
    
    while (1)
    {
        //clear the socket set
        FD_ZERO(&readfds);  // Xoa ds file descriptor

        //add socket server to fds
        FD_SET(server_fd, &readfds);

        //add all client socket to fds
        for (int i =0; i<max_clients; i++)
        {
            if(client_fd[i] >0)
            {
                FD_SET(client_fd[i], &readfds);
            }
            if(client_fd[i] > max_fd){
                max_fd = client_fd[i];
            }
        }
        //check status of socket 
        activity = select(max_fd +1, &readfds, NULL, NULL, NULL);   

        if(activity <0){
            perror("select()");
            exit(EXIT_FAILURE);
        }
        //Neu server socket co data, is new connection
        if(FD_ISSET(server_fd, &readfds))
        {
            int new_socket;
            socklen_t addrLen = sizeof(address);
            if((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrLen)) < 0 )
            {
                perror("accept()");
                exit(EXIT_FAILURE);
            }
            printf("New connection: socket fd = %d, ip = %s, port = %d\n", new_socket, inet_ntoa(address.sin_addr), ntohs(address.sin_port));

            //add new socket to client fds
            for(int i =0;i<max_clients; i++)
            {
                if(client_fd[i] == 0)
                {
                    client_fd[i] = new_socket;
                    break;
                }
            }
        }
        //check sockets of client
        for(int i=0; i< MAX_CLIENTS; i++)
        {
            if(FD_ISSET(client_fd[i], &readfds))
            {
                int valread;
                if((valread = read(client_fd[i], buffer, 1024)) ==0)
                {
                    //somebody disconnected
                    printf("Client disconect, socket fd = %d\n", client_fd);
                    close(client_fd[i]);
                    client_fd[i] = 0 ;
                }
                else
                {
                    //handle message
                    buffer[valread] == '\0';
                    printf("Message from client %d: %s\n",client_fd, buffer);
                }
            }
        }
        }
        return 0;

}