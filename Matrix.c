#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <locale.h>
#include <stdbool.h>
#include <wchar.h>

const char WIDTH  = 16 * 5; // Width and length of the Matrix display 
const char HEIGHT = 10 * 5;

const int CHAR_MIN = 33; // Min and max of the chars that can be displayed
const int CHAR_MAX = 126;

typedef struct mchar_t {
    char char_index; // The unicode index of the char
    char duration_remaining; // Amount of time until the char disappears

    bool is_head; // If this char is a head or not
    char x, y; // X and Y positions of the char
    char tail_length; // Length of the matrix thing
} mchar; // matrix char

int get_rand_num(int min, int max) {
    // Return a random number between min and max
    return (rand() % max) + min;
}

void display_matrix(mchar matrix[HEIGHT][WIDTH]) {
    for(int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x < WIDTH; x++) {
            printf("%c ", matrix[y][x].char_index);
        }

        printf("\n");
    }
}

void update_matrix(mchar matrix[HEIGHT][WIDTH]) {
    for(int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x < WIDTH; x++) {
            matrix[y][x].char_index = get_rand_num(CHAR_MIN, CHAR_MAX);
        }
    }
}

void set_matrix(mchar matrix[HEIGHT][WIDTH]) {
    for(int y = 0; y < HEIGHT; y++) {
        for(int x = 0; x < WIDTH; x++) {
            matrix[y][x].char_index = 0;
            matrix[y][x].duration_remaining = 0;

            matrix[y][x].is_head = 0;
            matrix[y][x].x = x;
            matrix[y][x].y = y;
            matrix[y][x].tail_length = 0;
        }
    }
}

int main() {
    setlocale(LC_ALL, ""); // Set the locale to support Unicode output
    srand(time(NULL)); // Set the random seed

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

    mchar matrix[HEIGHT][WIDTH]; // matrix chars that will be diplayed to the screen
    
    set_matrix(matrix); // Set all the mchars

    // This is where parent will be
    while(1) {
        system("clear"); // Clear the terminal
        
        update_matrix(matrix); // Update the matrix
        display_matrix(matrix); // Display the matrix

        fflush(stdout); // Put the print statment about directly to the terminal
        usleep(100000); // sleep for 0.1 seconds
    }

    system("clear"); // Clear terminal

    return 0;
}