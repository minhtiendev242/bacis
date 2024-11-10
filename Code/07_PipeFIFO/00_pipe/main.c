#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#define MSG_SIZE 20

char *msg1 ="hi, war1 #1";
char *msg2 ="hi, war2 #2";
char *msg3 ="hi, war3 #3";
char *msg4 ="hi, war4 #4";

char pipe_buff[MSG_SIZE];
int fds[2], i;

void sig_handler1(int num)
{
    printf("Im signal handler1: %d\n", num);
    write(fds[1], msg4, MSG_SIZE);
}
int main(int argc, char const *argv[])
{
    if(signal(SIGINT, sig_handler1) == SIG_ERR){
        fprintf(stderr, "Cannot handler SIGINT");
        exit(EXIT_FAILURE);
    }
    if(pipe(fds) <0){
        printf("pipe() unsuccessfully\n");
        exit(1);
    }

    // write(fds[1], msg1, MSG_SIZE);
    // write(fds[1], msg2, MSG_SIZE);
    // write(fds[1], msg3, MSG_SIZE);
    // printf("sleep 2 seconds\n");
    // sleep(2);

    read(fds[0], pipe_buff, MSG_SIZE);
    printf("msg[%d]: %s\n", 1, pipe_buff);
    
    // for(int i=0; i<3; i++){
    //     read(fds[0], pipe_buff, MSG_SIZE);
    //     printf("msg[%d]: %s\n", i+1, pipe_buff);
    // }
    // return 0;

}