#include <sys/un.h>
#include <sys/socket.h>
#include <stddef.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h> //  Chứa cấu trúc cần thiết cho socket.
#include <netinet/in.h> //  Thư viện chứa các hằng số, cấu trúc khi sử dụng địa chỉ trên internet
#include <arpa/inet.h>
#include <unistd.h>

#define BUF_SIZE 10
#define SOCK_PATH "./sock_stream"

int main(int argc, char *argv[])
{
    struct sockaddr_un svaddr;
    int fd;
    size_t msgLen;
    ssize_t numBytes; 
    char buff[BUF_SIZE] = {0};

    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(fd == -1)
        return 1;

    memset(&svaddr, 0, sizeof(struct sockaddr_un));
    svaddr.sun_family = AF_UNIX;
    strncpy(svaddr.sun_path, SOCK_PATH, sizeof(svaddr.sun_path)-1);

    if(connect(fd, (struct sockaddr *)&svaddr, sizeof(struct sockaddr)) !=0)
    {
        printf("connetion with the server failed...\n");
        return 1;
    }
    else
    {
        printf("Connected to the server.\n");
    }
    printf("send: %s\n", argv[1]);
    write(fd, argv[1], BUF_SIZE);

    while (1)
    {
        if(read(fd, buff, sizeof(buff))> 0)
            printf("From server: %s\n", buff);
    }
    return 0;
    
}