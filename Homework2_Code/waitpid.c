#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process\n");
        sleep(2); // Simulate work
    } else {
        // Parent process
        int status;
        pid_t child_pid = waitpid(pid, &status, 0);
        printf("Parent: Child %d finished with status %d\n", child_pid, status);
    }

    return 0;
}
