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
#define handler_error(msg) \
    do {perror(msg); exit(EXIT_FAILURE);} while (0)

void chat_func(int new_socket_fd)
{
    int num_read, num_write;
    char sendbuff[BUFF_SIZE];
    char recvbuff[BUFF_SIZE];

    while (1)
    {
        memset(sendbuff, '0', BUFF_SIZE);
        memset(recvbuff, '0', BUFF_SIZE);

        //Read from socket
        //Read_func block until read all data
        num_read = read(new_socket_fd, recvbuff, BUFF_SIZE);
        if(num_read == -1)
            handler_error("read()");
        if (strncmp("exit", recvbuff, 4)==0){
            system("clear");
            break;
        }
        printf("\nMessage from client: %s\n", recvbuff);

        printf("Please respond the message: ");
        fgets(sendbuff, BUFF_SIZE, stdin);

        num_write = write(new_socket_fd, sendbuff, sizeof(sendbuff));
        if(num_write ==-1)
            handler_error("write()");
        if (strncmp("exit", sendbuff, 4)==0){
            system("clear");
            break;
        }
        sleep (1);
        close(new_socket_fd);
    }
    
}

int main (int argc, char *argv[])
{
    int port_no, len, opt;
    int server_fd, new_socket_fd;
    struct sockaddr_in serv_addr, client_addr;

    //Read portnumber on cm line
    if(argc <2){
        printf("No port provide\ncommand: ./server <port number>\n");
        exit(EXIT_FAILURE);
    }else
        port_no = atoi(argv[1]);

    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    memset(&client_addr, 0, sizeof(struct sockaddr_in));

    //Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd == -1)
        handler_error("socket()");

     /* Ngăn lỗi : “address already in use” */
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        handler_error("setsockopt()");
    
    /* Khởi tạo địa chỉ cho server */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_no);
    serv_addr.sin_addr.s_addr = INADDR_ANY; //ip may

    //    /* Gắn socket với địa chỉ server */
    if(bind(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))== -1)
        handler_error("bind()");

    //listen max 5 connection on queue
    if(listen(server_fd, LISTEN_BACKLOG) == -1)
        handler_error("listen()");

    // Get info of client
        len = sizeof(client_addr);

    while (1)
    {
        printf("Server is listening at port: %d \n....\n", port_no);
        new_socket_fd = accept(server_fd, (struct sockaddr*)&client_addr, (socklen_t *)&len);
        if(new_socket_fd == -1)
            handler_error("accept()");
        system ("clear");
        printf("Server: got connection \n");
        chat_func(new_socket_fd);
    }
    close(server_fd);
    return 0;

}