#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd[2];
    pid_t pid1, pid2;

    // Create the pipe
    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed\n");
        exit(1);
    }

    // First child process
    pid1 = fork();
    if (pid1 < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (pid1 == 0) {
        // Child 1 process
        close(fd[0]);  // Close reading end of the pipe
        dup2(fd[1], STDOUT_FILENO);  // Redirect stdout to the pipe's writing end
        close(fd[1]);  // Close original writing end
        execlp("ls", "ls", NULL);  // Execute 'ls' command
    }

    // Second child process
    pid2 = fork();
    if (pid2 < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (pid2 == 0) {
        // Child 2 process
        close(fd[1]);  // Close writing end of the pipe
        dup2(fd[0], STDIN_FILENO);  // Redirect stdin to the pipe's reading end
        close(fd[0]);  // Close original reading end
        execlp("wc", "wc", "-l", NULL);  // Execute 'wc -l' command to count lines
    }

    // Parent process
    close(fd[0]);  // Close reading end in parent
    close(fd[1]);  // Close writing end in parent
    wait(NULL);  // Wait for both children to finish
    wait(NULL);

    return 0;
}
