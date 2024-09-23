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
        printf("hello\n");
    } else {
        // Parent process sleeps to let child print first
        sleep(1);
        printf("goodbye\n");
    }

    return 0;
}
