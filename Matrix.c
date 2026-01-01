#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

const int WIDTH, LENGTH = 100; // Width and length of the Matrix display

int main() {
    pid_t parent_pid = getpid();

    pid_t pid = fork(); // fork() makes a child process (a copy of the parent process which is this process) and gives each process a process id (pid)
    // fork() uses CPU cores if they are avalible 
    // If they aren't, 1 CPU core will do both process very fast

    if(pid < 0) {
        perror("Fork Fail\n");
        return 1;
    }

    //printf("Hello World, pid = %d\n", getpid());

    if(pid == 0) { // Child process
        getchar(); // wait for user to press enter
        if(kill(parent_pid, SIGTERM) == -1) {
            perror("Parent Kill Failed\n");
            return 1;
        }

        perror("Parent Kill Success\n");
    }

    while(1) {
        system("clear");
        printf("Time remaining: %d seconds\n", 2);
        fflush(stdout);
        usleep(100);
    }

    system("clear");

    return 0;
}