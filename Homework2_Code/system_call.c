#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#define NUM_ITERATIONS 1000000

int main() {
    struct timeval start, end;
    int i;
    gettimeofday(&start, NULL);
    for (i = 0; i < NUM_ITERATIONS; i++) {
        read(0, NULL, 0); // Perform a 0-byte read
    }
    gettimeofday(&end, NULL);
    double elapsed = (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
    printf("Average time per system call: %f microseconds\n", elapsed / NUM_ITERATIONS);
    return 0;
}
