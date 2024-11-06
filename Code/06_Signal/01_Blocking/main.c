#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

void sig_hanlder1(int signum){
    printf("Im signal handler1\n");
    exit(EXIT_SUCCESS);
}

int main(){
    //time_t start, finish;
    sigset_t new_set, old_set;
    if(signal(SIGINT, sig_hanlder1) == SIG_ERR){
        fprintf(stderr,"Cannot handler SIGINT");
        exit(EXIT_FAILURE);
    }

    sigemptyset(&new_set);
    sigemptyset(&old_set);
    sigaddset(&new_set, SIGINT);
    //sigaddset(&new_set, SIGCHLD);
    printf("new_set is %x\n", new_set);

    if(sigprocmask(SIG_SETMASK, &new_set, &old_set) ==0){
        // sigprocmask(SIG_SETMASK, NULL, &old_set);
        if(sigismember(&new_set, SIGINT)==1) {
            printf("SIGINT exist\n");
        }else if (sigismember(&new_set, SIGINT)==0){
            printf("SIGINT does not exist\n");
        }
    }
    while (1);
    return 0;
    
}