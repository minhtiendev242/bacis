#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>

#define FIFO_NAME "my_fifo"

void signal_handler(int signum) {
    printf("Child received SIGUSR1 signal from Parent.\n");
}

// write func for parent
void* parent_write_thread(void* arg) {
    int fifo_fd = *((int*)arg);
    char message[] = "Hello from Parent";
    while (1) {
        write(fifo_fd, message, strlen(message) + 1);
        printf("Parent sent message to FIFO.\n");
        sleep(5);  
    }
    return NULL;
}

// read func for child thread
void* child_read_thread(void* arg) {
    int fifo_fd = *((int*)arg);
    char buffer[100];
    while (1) {
        int bytes = read(fifo_fd, buffer, sizeof(buffer));
        if (bytes > 0) {
            printf("Child received message: %s\n", buffer);
        }
    }
    return NULL;
}

int main() {
    // Tạo FIFO
    int fifo_test;
    fifo_test = mkfifo(FIFO_NAME, 0666);

    //handler error for create fifo
    if (fifo_test < 0) {
            perror("Mkfifo failed!");
            exit(1);
        }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {  // Child
        signal(SIGUSR1, signal_handler);  

        // openFifo to read
        int fifo_fd = open(FIFO_NAME, O_RDONLY);
        if (fifo_fd < 0) {
            perror("Child failed to open FIFO");
            exit(1);
        }

        // create read thread
        pthread_t read_thread;
        pthread_create(&read_thread, NULL, child_read_thread, &fifo_fd);

        // wait signal SIGUSR1 from parent
        while (1) {
            pause();  
        }

        pthread_join(read_thread, NULL);
        close(fifo_fd);
    } else {  // Parent
        // open FIFO to write
        int fifo_fd = open(FIFO_NAME, O_WRONLY);
        if (fifo_fd < 0) {
            perror("Parent failed to open FIFO");
            exit(1);
        }

        pthread_t write_thread;
        pthread_create(&write_thread, NULL, parent_write_thread, &fifo_fd);

        // sent signal to child
        while (1) {
            sleep(6);  
            kill(pid, SIGUSR1); 
            printf("Parent sent SIGUSR1 signal to Child.\n");
        }

        pthread_join(write_thread, NULL);
        close(fifo_fd);
    }


    unlink(FIFO_NAME);


    return 0;
}
