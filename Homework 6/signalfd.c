#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/signalfd.h>
#include <signal.h>
#include <poll.h>

int main() {
    sigset_t mask;
    struct signalfd_siginfo fdsi;
    int sfd;

    // Block signals and set up the signal mask
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGTERM);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    // Create a signalfd to handle signals
    sfd = signalfd(-1, &mask, 0);
    if (sfd == -1) {
        perror("signalfd");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for signals (SIGINT, SIGTERM)...\n");
    
    struct pollfd fds[1] = {
        { .fd = sfd, .events = POLLIN },
    };

    while (1) {
        if (poll(fds, 1, -1) == -1) {
            perror("poll");
            exit(EXIT_FAILURE);
        }

        if (read(sfd, &fdsi, sizeof(fdsi)) != sizeof(fdsi)) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if (fdsi.ssi_signo == SIGINT) {
            printf("Received SIGINT\n");
            break;
        } else if (fdsi.ssi_signo == SIGTERM) {
            printf("Received SIGTERM\n");
            break;
        }
    }

    close(sfd);
    return 0;
}
