#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h> //  Chứa cấu trúc cần thiết cho socket.
#include <netinet/in.h> //  Thư viện chứa các hằng số, cấu trúc khi sử dụng địa chỉ trên internet
#include <arpa/inet.h>
#include <unistd.h>

#define LISTEN_BACKLOG 50
#define BUFF_SIZE 256
#define handler_err(msg) \
   do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0);

    void chat_func(int new_socket_fd)
    {
        int numb_read, numb_write;
        char sendbuff[BUFF_SIZE];
        char recvbuff[BUFF_SIZE];

        while(1)
        {
            memset(sendbuff, '0', BUFF_SIZE);
            memset(recvbuff, '0', BUFF_SIZE);

            numb_read = read(new_socket_fd, recvbuff, BUFF_SIZE);
            if(numb_read == -1)
                handler_err("read()");
            if (strncmp("exit", recvbuff, 4) ==0)
            {
                system("clear");
                break;
            }
            printf("Please respond the message:");
            fgets(sendbuff, BUFF_SIZE, stdin);

            numb_write = write(new_socket_fd, sendbuff, sizeof(sendbuff));
            if (numb_write == -1)
                handler_err("write()");
                
            if(strncmp("exit", sendbuff, 4) ==0)
            {
                system("claer");
                break;
            }
            sleep (1);
        }
        close(new_socket_fd);
    }

    int main(int argc, char *argv[])
    {
        int port_no, len, opt;
        int server_fd, new_socket_fd;
        struct sockaddr_in serv_addr, client_addr;

        if(argc<2)
        {
            printf("No port provide\n command: ./server <port number>\n");
            exit(EXIT_FAILURE);
        }
        else
            port_no = atoi(argv[1]); //Atoi = ASCII to Integer

        memset(&serv_addr, 0, sizeof(struct sockaddr_in));
        memset(&client_addr, 0, sizeof(struct sockaddr_in));

        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if(server_fd == -1)
            handler_err("socket()");

        if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
            handler_err("setsockopt()");

            serv_addr.sin_family = AF_INET;
            serv_addr.sin_port = htons(port_no);
            serv_addr.sin_addr.s_addr = INADDR_ANY;

        //bind Socket to server
            if(bind(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
                handler_err("bind()");

            if(listen(server_fd, LISTEN_BACKLOG) == -1)
                handler_err("listen()");
            
            len = sizeof(client_addr);

            while(1)
            {
                printf("Server is listening at port: %d \n....\n", port_no);
                new_socket_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&len);
                if(new_socket_fd == -1)
                    handler_err("accpet()");

                system("clear");

                printf("Server: got connection \n");
                chat_func(new_socket_fd);
            }
            close(server_fd);
            return 0;
    }