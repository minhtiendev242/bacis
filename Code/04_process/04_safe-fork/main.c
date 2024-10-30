#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void func(int signum)
{
	printf("Im in func()\n");
	wait(NULL);
}

int main()
{
        pid_t child_pid;
        child_pid =fork();

        if(child_pid >=0){
                if(child_pid == 0){
                        printf("I am Child, myPID: %d\n", getpid());
			while(1);
                }else {
			signal(SIGCHLD, func);
			printf("I am Parent\n");
                	 while (1);
                }
        }else{
                printf("fork() unsuccessfully\n");
        }
        return 0;
}
           
