#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <locale.h>

const int WIDTH, LENGTH = 100; // Width and length of the Matrix display

int main() {
    setlocale(LC_ALL, ""); // Set the locale to support Unicode output
    pid_t parent_pid = getpid(); // Get the parent process id

    pid_t pid = fork(); // fork() makes a child process (a copy of the parent process which is this process) and gives each process a process id (pid)
    // fork() uses CPU cores if they are avalible 
    // If they aren't, 1 CPU core will do both process very fast

    if(pid < 0) { // Process id < 0 means there was an error
        perror("Fork Fail\n");
        return 1;
    }

    //printf("Hello World, pid = %d\n", getpid());

    if(pid == 0) { // Child process
        getchar(); // Wait for user to press enter
        if(kill(parent_pid, SIGTERM) == -1) { // Kill parent process with safety nets
            perror("Parent Kill Failed\n");
            return 1;
        }
    
        system("clear");
        kill(getpid(), SIGTERM); // Also kill the now orphan process
    }

    int char_displayed = 0x0041;

    // This is where parent will be
    while(1) {
        system("clear"); // Clear the terminal
        printf("%lc\n", (wchar_t)char_displayed);
        char_displayed++;
        fflush(stdout); // Put the print statment about directly to the terminal
        usleep(25000); // sleep for 0.1 seconds
    }

    system("clear"); // Clear terminal

    return 0;
}