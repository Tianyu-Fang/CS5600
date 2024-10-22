## Command to Run the pidfd
gcc -o pidfd pidfd.c
./pidfd

## Command to Run the signalfd
gcc -o signalfd signalfd.c
./signalfd

## Command to Run the userfaultfd
gcc -o userfaultfd_example userfaultfd_example.c -lpthread
./userfaultfd_example

**1. signalfd**
The signalfd system call allows Linux programs to handle signals through file descriptors, offering a cleaner and more synchronous way to manage signals compared to traditional signal handling. By converting signals into events that can be handled using pollable file descriptors, programs can avoid the typical pitfalls of asynchronous signal handling (like race conditions or disrupted system calls). It works well with polling mechanisms like poll() or epoll() for consolidated I/O and signal handling, improving robustness in multi-threaded applications.

**2. pidfd**
The pidfd system call provides a file descriptor that references a specific process via its PID. It allows processes to interact with or wait for other processes without race conditions (like PID reuse). By using pidfd_open(), processes can create a pidfd to monitor the state of another process, such as waiting for its termination (pidfd_send_signal() for signaling, and poll() for monitoring). It’s especially useful for avoiding issues tied to traditional signal-based process monitoring in complex systems.

**3. userfaultfd**
The userfaultfd system call allows applications to handle page faults in user space. It is typically used in scenarios like live migration of virtual machines or custom memory management. A process registers a memory range, and when a page fault occurs in this range, the kernel suspends the faulting thread and sends an event via a file descriptor. This enables the user-space program to dynamically allocate or load the required memory, giving more control over memory management to the user space.

## Comparison of signalfd, pidfd, and userfaultfd:

**signalfd:**
Complexity: Moderate.
Use Case: Primarily used to handle asynchronous signals in a more synchronous and predictable manner, especially in programs that already rely on pollable file descriptors.
Summary: Simplifies signal handling by converting signals into events that can be handled with poll or epoll.

**pidfd:**
Complexity: Low to Moderate.
Use Case: Used for managing and monitoring processes through file descriptors without race conditions or PID reuse issues.
Summary: Useful for signaling or waiting on processes in a race-free manner.

**userfaultfd:**
Complexity: High.
Use Case: Used for handling page faults in user space, providing fine control over memory management. Common in advanced scenarios like live VM migration or customized memory paging.
Summary: Allows applications to handle page faults dynamically, making it more flexible but complex.

**Summary:**
signalfd simplifies signal handling by transforming signals into manageable events.
pidfd is great for race-free process management, offering a simpler way to interact with processes compared to traditional signals.
userfaultfd offers high flexibility in memory management, but with increased complexity, making it suitable for specialized cases like VM migration.
