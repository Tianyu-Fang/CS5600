#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/userfaultfd.h>
#include <sys/mman.h>
#include <pthread.h>
#include <poll.h>
#include <fcntl.h>
#include <errno.h>

#define PAGE_SIZE 4096

void* fault_handler_thread(void* arg) {
    int uffd = *(int*)arg;
    struct uffd_msg msg;

    while (1) {
        struct pollfd pollfd = { .fd = uffd, .events = POLLIN };
        if (poll(&pollfd, 1, -1) == -1) {
            perror("poll");
            exit(EXIT_FAILURE);
        }

        if (read(uffd, &msg, sizeof(msg)) != sizeof(msg)) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if (msg.event == UFFD_EVENT_PAGEFAULT) {
            printf("Page fault at address: %p\n", (void*)msg.arg.pagefault.address);
            // Handle the fault (e.g., map a new page here)
        }
    }
}

int main() {
    int uffd;
    pthread_t thr;
    void* fault_page;

    // Create userfaultfd
    uffd = syscall(SYS_userfaultfd, O_CLOEXEC | O_NONBLOCK);
    if (uffd == -1) {
        perror("userfaultfd");
        exit(EXIT_FAILURE);
    }

    struct uffdio_api uffdio_api = { .api = UFFD_API };
    if (ioctl(uffd, UFFDIO_API, &uffdio_api) == -1) {
        perror("ioctl-UFFDIO_API");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for page handling
    fault_page = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (fault_page == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Register memory region with userfaultfd
    struct uffdio_register uffdio_register = {
        .mode = UFFDIO_REGISTER_MODE_MISSING,
        .range = { .start = (unsigned long)fault_page, .len = PAGE_SIZE }
    };

    if (ioctl(uffd, UFFDIO_REGISTER, &uffdio_register) == -1) {
        perror("ioctl-UFFDIO_REGISTER");
        exit(EXIT_FAILURE);
    }

    // Start the fault handler thread
    if (pthread_create(&thr, NULL, fault_handler_thread, &uffd) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    printf("Accessing fault page to trigger userfaultfd.\n");
    *(char*)fault_page = 'A';  // Trigger a page fault

    pthread_join(thr, NULL);
    return 0;
}
