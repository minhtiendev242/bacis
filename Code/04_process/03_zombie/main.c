#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	pid_t child_pid;
	int status;
	int counter=0;

	child_pid =fork();
	if(child_pid >=0){
		if(0 == child_pid){
			printf("Child process termination\n");
		}else {
		//	while (1);
			wait(&status);
		}
	}else{
		printf("fork() unsuccessfully\n");
	}
	return 0;
}
