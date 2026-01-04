#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <locale.h>
#include <stdbool.h>

const int WIDTH  = 100; // Width and length of the Matrix display 
const int HEIGHT = 100;


typedef struct mchar_t {
    unsigned short char_index; // The unicode index of the char
    char duration_remaining; // Amount of time until the char disappears

    bool is_head; // If this char is a head or not
    char x, y; // X and Y positions of the char
    char tail_length; // Length of the matrix thing
} mchar; // matrix char

void update_display(mchar display[HEIGHT][WIDTH]) {
    printf("%d : %d\n", WIDTH, HEIGHT);
    
    for(int x = 0; x < WIDTH; x++) {
        for(int y = 0; y < HEIGHT; y++) {
            printf("%c ", (wchar_t)display[y][x].is_head);
        }

        printf("\n");
    }
}

int main() {
    setlocale(LC_ALL, ""); // Set the locale to support Unicode output
    pid_t parent_pid = getpid(); // Get the parent process id

    pid_t pid = fork(); // fork() makes a child process (a copy of the parent process which is this process) and gives each process a process id (pid)
    // fork() uses CPU cores if they are avalible 
    // If they aren't, 1 CPU core will do both process very fast

    if(pid < 0) { // Process id < 0 means there was an error
        printf("Failed to fork\n");
        return 1;
    }

    //printf("Hello World, pid = %d\n", getpid());

    if(pid == 0) { // Child process
        getchar(); // Wait for user to press enter
        if(kill(parent_pid, SIGTERM) == -1) { // Kill parent process with safety nets
            printf("Parent kill failed\n");
            _exit(1);
        }
    
        system("clear");
        kill(getpid(), SIGTERM); // Also kill the now orphan process
    }

    mchar display[HEIGHT][WIDTH]; // matrix chars that will be diplayed to the screen

    
    // This is where parent will be
    while(1) {
        system("clear"); // Clear the terminal
        update_display(display);
        fflush(stdout); // Put the print statment about directly to the terminal
        usleep(100000); // sleep for 0.1 seconds
    }

    system("clear"); // Clear terminal

    return 0;
}