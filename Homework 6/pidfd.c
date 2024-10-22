#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        printf("Child process started.\n");
        sleep(5);  // Simulate some work
        printf("Child process exiting.\n");
        exit(0);
    } else {
        // Parent process
        int pidfd = syscall(SYS_pidfd_open, pid, 0);  // Open a pidfd for the child process
        if (pidfd == -1) {
            perror("pidfd_open");
            exit(EXIT_FAILURE);
        }

        printf("Waiting for the child process to finish using pidfd.\n");
        struct pollfd pfd = {
            .fd = pidfd,
            .events = POLLIN,
        };

        if (poll(&pfd, 1, -1) == -1) {
            perror("poll");
            exit(EXIT_FAILURE);
        }

        printf("Child process has exited.\n");
        close(pidfd);
    }

    return 0;
}
