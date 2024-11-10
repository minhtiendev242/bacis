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
        fd = open(FIFO_FILE, O_RDONLY);
        read(fd, buff, BUFF_SIZE);
        
        printf("producer message: %s", buff);
        close(fd);

        printf("Message to producer: ");
        fflush(stdin);
        fgets(buff, BUFF_SIZE, stdin);
        fd = open(FIFO_FILE, O_WRONLY);
        write(fd, buff, strlen(buff)+1);
    }
    return 0;
}