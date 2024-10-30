#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	pid_t child_pid;
	int status, rv;

	child_pid = fork();
	if(child_pid >= 0){
		if(0 == child_pid){
			printf("Im the child process, my PID: %d\n", getpid());
			//while(1);
			sleep(3);
			exit(0);
		}else{
			rv = wait(&status);
			if(rv == -1){
				printf("wait() unsuccessful\n");
			}
			printf("\nIm the parent process, PID child process: %d\n", rv);
			if(WIFEXITED(status)){
				printf("Normally termination, status = %d\n", WEXITSTATUS(status));
			}else if(WIFSIGNALED(status)){
				printf("killed by signal, value = %d\n", WTERMSIG(status));
			}
		}
		return 0;
	}
}
