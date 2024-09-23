#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/time.h>

#define NUM_ITERATIONS 100000
#define PIPE_READ 0
#define PIPE_WRITE 1

void bind_to_cpu(int cpu_id) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(cpu_id, &cpuset);
    sched_setaffinity(0, sizeof(cpu_set_t), &cpuset);
}

int main() {
    int pipe1[2], pipe2[2];
    pid_t pid;
    struct timeval start, end;

    pipe(pipe1);
    pipe(pipe2);

    if ((pid = fork()) == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) { // Child process
        bind_to_cpu(0); // Bind to CPU 0
        char buf;
        for (int i = 0; i < NUM_ITERATIONS; i++) {
            read(pipe1[PIPE_READ], &buf, 1);
            write(pipe2[PIPE_WRITE], &buf, 1);
        }
    } else { // Parent process
        bind_to_cpu(0); // Bind to CPU 0
        char buf = 'c';
        gettimeofday(&start, NULL);
        for (int i = 0; i < NUM_ITERATIONS; i++) {
            write(pipe1[PIPE_WRITE], &buf, 1);
            read(pipe2[PIPE_READ], &buf, 1);
        }
        gettimeofday(&end, NULL);
        double elapsed = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
        printf("Average time per context switch: %f microseconds\n", elapsed / (2 * NUM_ITERATIONS));
    }

    return 0;
}
