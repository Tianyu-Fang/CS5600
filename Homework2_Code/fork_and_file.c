#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("testfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        fprintf(stderr, "Failed to open file\n");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (pid == 0) {
        // Child process
        write(fd, "Child writing\n", 14);
    } else {
        // Parent process
        write(fd, "Parent writing\n", 15);
    }

    close(fd);
    return 0;
}
