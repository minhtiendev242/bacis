#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define FIFO_FILE "./myfifo"
#define BUFF_SIZE 1024

int main(int argc, char const *argv[]){
    char buff[BUFF_SIZE];
    int fd;

    mkfifo(FIFO_FILE, 0666);

    while(1){
        //write
        printf("Message to consumer:");
        fflush(stdin);
        fgets(buff, BUFF_SIZE, stdin);

        fd = open(FIFO_FILE, O_WRONLY);
        write(fd, buff, strlen(buff) +1);
        //close(fd);

        fd = open(FIFO_FILE, O_RDONLY);
        read(fd, buff, BUFF_SIZE);
        //close(fd);

        printf("comsumer response: %s", buff);
        //close(fd);
    }
    return 0;
}
