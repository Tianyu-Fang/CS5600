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
        execl("/bin/ls", "ls", NULL);
        // other variants can be tested similarly
    } else {
        // Parent process
        wait(NULL); // Parent waits for child
        printf("Done with exec example\n");
    }

    return 0;
}
