#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int x = 100;
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child: x = %d\n", x);
        x = 200;
        printf("Child: x changed to %d\n", x);
    } else {
        // Parent process
        printf("Parent: x = %d\n", x);
        x = 300;
        printf("Parent: x changed to %d\n", x);
    }

    return 0;
}
