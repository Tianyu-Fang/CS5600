#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (pid == 0) {
        // Child process
        close(STDOUT_FILENO); // Close standard output
        printf("This will not be printed to the screen\n");
    } else {
        // Parent process
        printf("Parent process\n");
    }

    return 0;
}
