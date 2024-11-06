#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

void handler_SIGINT(int num)
{
    printf("\nIm signal SIGINT: %d\n", num);
    exit(EXIT_SUCCESS);
}
void sig_handler_user(int num)
{
    if(num == SIGUSR1){
          printf("\nIm signal User1: %d\n", num);
    }else if(num == SIGUSR2){
        printf("\nIm signal User2: %d\n", num);
    }
    wait(NULL);
}


int main()
{
    signal(SIGINT, handler_SIGINT);
    signal(SIGUSR1, sig_handler_user);
    signal(SIGUSR2, sig_handler_user);

    pid_t child_pid = fork();
    if(child_pid >= 0){
        if(0 == child_pid)
        {
            int child = getpid();
            printf("Child id process: %d\n", child);
            kill(child, SIGUSR1);
            sleep(1);
            kill(child, SIGUSR2);
            sleep(1);
            while (1);
        }else
        {
            printf("Parent PID: %d\n", getppid());
            while (1);
        }
    }else
    {
        printf("fork() unsuccessfully\n");
    }
    return 0;
}