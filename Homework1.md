# CS5600 Homework 1

# Homework 1 
## Question1
(base) tianyu@Tianyus-MBP ~ % cd Downloads
(base) tianyu@Tianyus-MBP Downloads % python3 process-run.py -l 5:100,5:100 -c -p

Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1          
  2        RUN:cpu         READY             1          
  3        RUN:cpu         READY             1          
  4        RUN:cpu         READY             1          
  5        RUN:cpu         READY             1          
  6           DONE       RUN:cpu             1          
  7           DONE       RUN:cpu             1          
  8           DONE       RUN:cpu             1          
  9           DONE       RUN:cpu             1          
 10           DONE       RUN:cpu             1          

Stats: Total Time 10
Stats: CPU Busy 10 (100.00%)
Stats: IO Busy  0 (0.00%)
- **What should the CPU utilization be (e.g., the percent of time the CPU is in use?)**
- 100%

- **Why do you know this? Use the -c and -p flags tosee if you were right.**
- The 5:100 means that each process will run 5 instructions, and 100% of those instructions are CPU-bound. Since there are no I/O operations, the CPU will be continuously busy throughout the entire execution, resulting in full utilization.

#  Question 2
(base) tianyu@Tianyus-MBP Downloads % python3 process-run.py -l 4:100,1:0 -c -p

Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1          
  2        RUN:cpu         READY             1          
  3        RUN:cpu         READY             1          
  4        RUN:cpu         READY             1          
  5           DONE        RUN:io             1          
  6           DONE       BLOCKED                           1
  7           DONE       BLOCKED                           1
  8           DONE       BLOCKED                           1
  9           DONE       BLOCKED                           1
 10           DONE       BLOCKED                           1
 11*          DONE   RUN:io_done             1          

Stats: Total Time 11
Stats: CPU Busy 6 (54.55%)
Stats: IO Busy  5 (45.45%)

- **How long does it take to complete both processes?**
- 11 clock ticks, CPU busy for 6 ticks, and I/O busy for 5 ticks.

#  Question 3
(base) tianyu@Tianyus-MBP Downloads % python3 process-run.py -l 1:0,4:100 -c -p

Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1          
  2        BLOCKED       RUN:cpu             1             1
  3        BLOCKED       RUN:cpu             1             1
  4        BLOCKED       RUN:cpu             1             1
  5        BLOCKED       RUN:cpu             1             1
  6        BLOCKED          DONE                           1
  7*   RUN:io_done          DONE             1          

Stats: Total Time 7
Stats: CPU Busy 6 (85.71%)
Stats: IO Busy  5 (71.43%)

- **What happens now? Does switching the order matter? Why?**
- After switching the order, the total time to complete both processes is 7 clock ticks.
CPU Busy Time: The CPU was busy for 6 clock ticks (1 tick for the I/O initiation + 4 ticks for the CPU-bound process + 1 tick for I/O completion).
I/O Busy Time: The I/O was busy for 5 clock ticks (clock ticks 2 to 6).
Therefore, switching the order matters, it leads to CPU work and I/O wait time overlap, which makes the system more efficient and reduces the overall execution time.

#  Question 4
(base) tianyu@Tianyus-MBP Downloads % python3 process-run.py -l 1:0,4:100 -c -S SWITCH_ON_END -p

Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1          
  2        BLOCKED         READY                           1
  3        BLOCKED         READY                           1
  4        BLOCKED         READY                           1
  5        BLOCKED         READY                           1
  6        BLOCKED         READY                           1
  7*   RUN:io_done         READY             1          
  8           DONE       RUN:cpu             1          
  9           DONE       RUN:cpu             1          
 10           DONE       RUN:cpu             1          
 11           DONE       RUN:cpu             1          

Stats: Total Time 11
Stats: CPU Busy 6 (54.55%)
Stats: IO Busy  5 (45.45%)       

- **What happens when you run the following two processes (-l 1:0,4:100 -c -S SWITCH ON END), one doing I/O and the other doing CPU work?**
- The SWITCH_ON_END flag causes the system to wait for Process 0 (the I/O-bound process) to complete its I/O before running Process 1 (the CPU-bound process). Therefore, the CPU remains idle during the I/O wait time (ticks 2 to 6), which makes the total execution time longer (11 ticks) compared to a more efficient system where the CPU can run the next process during I/O waits.

#  Question 5
(base) tianyu@Tianyus-MBP Downloads % python3 process-run.py -l 1:0,4:100 -c -S SWITCH_ON_IO -p

Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1          
  2        BLOCKED       RUN:cpu             1             1
  3        BLOCKED       RUN:cpu             1             1
  4        BLOCKED       RUN:cpu             1             1
  5        BLOCKED       RUN:cpu             1             1
  6        BLOCKED          DONE                           1
  7*   RUN:io_done          DONE             1          

Stats: Total Time 7
Stats: CPU Busy 6 (85.71%)
Stats: IO Busy  5 (71.43%)

- **What happens now?**
- With the SWITCH_ON_IO flag, the CPU was used more efficiently because the system switched to Process 1 during the I/O wait time of Process 0. The total execution time was reduced to 7 clock ticks, compared to 11 ticks when using SWITCH_ON_END, as the CPU did not remain idle. This demonstrates that switching to another process during I/O waits leads to better resource utilization and faster completion of both processes.

- **Comparison with previous run in Question 4**
- In contrast to using SWITCH_ON_END (which resulted in 11 clock ticks), the total time is now 7 clock ticks because the system efficiently switches to Process 1 during the I/O wait time of Process 0. The key difference is that the CPU was not idle during the I/O wait. The SWITCH_ON_IO flag allows the system to utilize the CPU while Process 0 is waiting for I/O to finish, making the process more efficient.

#  Question 6
(base) tianyu@Tianyus-MBP Downloads % python3 process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -c -p -I IO_RUN_LATER

Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
  1         RUN:io         READY         READY         READY             1          
  2        BLOCKED       RUN:cpu         READY         READY             1             1
  3        BLOCKED       RUN:cpu         READY         READY             1             1
  4        BLOCKED       RUN:cpu         READY         READY             1             1
  5        BLOCKED       RUN:cpu         READY         READY             1             1
  6        BLOCKED       RUN:cpu         READY         READY             1             1
  7*         READY          DONE       RUN:cpu         READY             1          
  8          READY          DONE       RUN:cpu         READY             1          
  9          READY          DONE       RUN:cpu         READY             1          
 10          READY          DONE       RUN:cpu         READY             1          
 11          READY          DONE       RUN:cpu         READY             1          
 12          READY          DONE          DONE       RUN:cpu             1          
 13          READY          DONE          DONE       RUN:cpu             1          
 14          READY          DONE          DONE       RUN:cpu             1          
 15          READY          DONE          DONE       RUN:cpu             1          
 16          READY          DONE          DONE       RUN:cpu             1          
 17    RUN:io_done          DONE          DONE          DONE             1          
 18         RUN:io          DONE          DONE          DONE             1          
 19        BLOCKED          DONE          DONE          DONE                           1
 20        BLOCKED          DONE          DONE          DONE                           1
 21        BLOCKED          DONE          DONE          DONE                           1
 22        BLOCKED          DONE          DONE          DONE                           1
 23        BLOCKED          DONE          DONE          DONE                           1
 24*   RUN:io_done          DONE          DONE          DONE             1          
 25         RUN:io          DONE          DONE          DONE             1          
 26        BLOCKED          DONE          DONE          DONE                           1
 27        BLOCKED          DONE          DONE          DONE                           1
 28        BLOCKED          DONE          DONE          DONE                           1
 29        BLOCKED          DONE          DONE          DONE                           1
 30        BLOCKED          DONE          DONE          DONE                           1
 31*   RUN:io_done          DONE          DONE          DONE             1          

Stats: Total Time 31
Stats: CPU Busy 21 (67.74%)
Stats: IO Busy  15 (48.39%)

- **What happens when you run this combination of processes?**
1. At Tick 1, Process 0 runs and issues an I/O request.
2. From Tick 2 to Tick 6, Process 1 runs all its CPU-bound instructions. Process 0 is waiting for I/O during this time.
3. At Tick 7, Process 0's I/O completes (RUN:io_done), but instead of running immediately, Process 2 starts its CPU work because of the IO_RUN_LATER flag.
4. Process 2 runs from Tick 7 to Tick 11.
5. Process 3 runs from Tick 12 to Tick 16.
6. After Process 3 finishes, Process 0 resumes at Tick 17, handling its second I/O operation.
7. The same behavior repeats: Process 0 issues its second I/O at Tick 19, and the CPU stays idle while waiting for the I/O to complete.
8. Process 0 finishes all its I/O requests by Tick 31.
- The IO_RUN_LATER flag causes unnecessary delays in running the I/O-bound process after its I/O completes. As a result, system resources are not being utilized effectively, leading to a longer total execution time (31 clock ticks) and suboptimal CPU and I/O parallelism.

#  Question 7
(base) tianyu@Tianyus-MBP Downloads % python3 process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -c -p -I IO_RUN_IMMEDIATE

Time        PID: 0        PID: 1        PID: 2        PID: 3           CPU           IOs
  1         RUN:io         READY         READY         READY             1          
  2        BLOCKED       RUN:cpu         READY         READY             1             1
  3        BLOCKED       RUN:cpu         READY         READY             1             1
  4        BLOCKED       RUN:cpu         READY         READY             1             1
  5        BLOCKED       RUN:cpu         READY         READY             1             1
  6        BLOCKED       RUN:cpu         READY         READY             1             1
  7*   RUN:io_done          DONE         READY         READY             1          
  8         RUN:io          DONE         READY         READY             1          
  9        BLOCKED          DONE       RUN:cpu         READY             1             1
 10        BLOCKED          DONE       RUN:cpu         READY             1             1
 11        BLOCKED          DONE       RUN:cpu         READY             1             1
 12        BLOCKED          DONE       RUN:cpu         READY             1             1
 13        BLOCKED          DONE       RUN:cpu         READY             1             1
 14*   RUN:io_done          DONE          DONE         READY             1          
 15         RUN:io          DONE          DONE         READY             1          
 16        BLOCKED          DONE          DONE       RUN:cpu             1             1
 17        BLOCKED          DONE          DONE       RUN:cpu             1             1
 18        BLOCKED          DONE          DONE       RUN:cpu             1             1
 19        BLOCKED          DONE          DONE       RUN:cpu             1             1
 20        BLOCKED          DONE          DONE       RUN:cpu             1             1
 21*   RUN:io_done          DONE          DONE          DONE             1          

Stats: Total Time 21
Stats: CPU Busy 21 (100.00%)
Stats: IO Busy  15 (71.43%)

- **How doesthis behavior differ?**
- The key differences are:
1. After Process 0 (the I/O-bound process) completes an I/O operation, it resumes immediately rather than waiting for the CPU-bound processes to finish. For example, at tick 7 and tick 14, you see RUN:io_done, meaning Process 0 resumes right after its I/O completes, rather than waiting for the other processes to finish.
2. The total time to complete all processes is 21 clock ticks, which is shorter compared to the IO_RUN_LATER case (which took 31 ticks). This reduction in time is due to the I/O-bound process being able to resume immediately, leading to more efficient execution.
3. The CPU Busy Time is 100% in this case because the CPU is always busy, either executing the CPU-bound processes or immediately resuming the I/O-bound process after each I/O completes. In contrast, with IO_RUN_LATER, there were idle periods where the CPU had to wait for the I/O-bound process to be scheduled, leading to a lower CPU utilization.

-  **Why might running a process that just completed an I/O again be a good idea?**
- Reduces latency, provides better parallelism, and improves resource utilization, which is faster in the overall execution.

#  Question 8
(base) tianyu@Tianyus-MBP Downloads % python3 process-run.py -s 1 -l 3:50,3:50 -c -p

Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1          
  2         RUN:io         READY             1          
  3        BLOCKED       RUN:cpu             1             1
  4        BLOCKED       RUN:cpu             1             1
  5        BLOCKED       RUN:cpu             1             1
  6        BLOCKED          DONE                           1
  7        BLOCKED          DONE                           1
  8*   RUN:io_done          DONE             1          
  9         RUN:io          DONE             1          
 10        BLOCKED          DONE                           1
 11        BLOCKED          DONE                           1
 12        BLOCKED          DONE                           1
 13        BLOCKED          DONE                           1
 14        BLOCKED          DONE                           1
 15*   RUN:io_done          DONE             1          

Stats: Total Time 15
Stats: CPU Busy 8 (53.33%)
Stats: IO Busy  10 (66.67%)

(base) tianyu@Tianyus-MBP Downloads % python3 process-run.py -s 2 -l 3:50,3:50 -c -p

Time        PID: 0        PID: 1           CPU           IOs
  1         RUN:io         READY             1          
  2        BLOCKED       RUN:cpu             1             1
  3        BLOCKED        RUN:io             1             1
  4        BLOCKED       BLOCKED                           2
  5        BLOCKED       BLOCKED                           2
  6        BLOCKED       BLOCKED                           2
  7*   RUN:io_done       BLOCKED             1             1
  8         RUN:io       BLOCKED             1             1
  9*       BLOCKED   RUN:io_done             1             1
 10        BLOCKED        RUN:io             1             1
 11        BLOCKED       BLOCKED                           2
 12        BLOCKED       BLOCKED                           2
 13        BLOCKED       BLOCKED                           2
 14*   RUN:io_done       BLOCKED             1             1
 15        RUN:cpu       BLOCKED             1             1
 16*          DONE   RUN:io_done             1          

Stats: Total Time 16
Stats: CPU Busy 10 (62.50%)
Stats: IO Busy  14 (87.50%)

(base) tianyu@Tianyus-MBP Downloads % python3 process-run.py -s 3 -l 3:50,3:50 -c -p

Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1          
  2         RUN:io         READY             1          
  3        BLOCKED        RUN:io             1             1
  4        BLOCKED       BLOCKED                           2
  5        BLOCKED       BLOCKED                           2
  6        BLOCKED       BLOCKED                           2
  7        BLOCKED       BLOCKED                           2
  8*   RUN:io_done       BLOCKED             1             1
  9*       RUN:cpu         READY             1          
 10           DONE   RUN:io_done             1          
 11           DONE        RUN:io             1          
 12           DONE       BLOCKED                           1
 13           DONE       BLOCKED                           1
 14           DONE       BLOCKED                           1
 15           DONE       BLOCKED                           1
 16           DONE       BLOCKED                           1
 17*          DONE   RUN:io_done             1          
 18           DONE       RUN:cpu             1          

Stats: Total Time 18
Stats: CPU Busy 9 (50.00%)
Stats: IO Busy  11 (61.11%)

(base) tianyu@Tianyus-MBP Downloads % python3 process-run.py -s 1 -l 3:50,3:50 -c -p -I IO_RUN_IMMEDIATE

Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1          
  2         RUN:io         READY             1          
  3        BLOCKED       RUN:cpu             1             1
  4        BLOCKED       RUN:cpu             1             1
  5        BLOCKED       RUN:cpu             1             1
  6        BLOCKED          DONE                           1
  7        BLOCKED          DONE                           1
  8*   RUN:io_done          DONE             1          
  9         RUN:io          DONE             1          
 10        BLOCKED          DONE                           1
 11        BLOCKED          DONE                           1
 12        BLOCKED          DONE                           1
 13        BLOCKED          DONE                           1
 14        BLOCKED          DONE                           1
 15*   RUN:io_done          DONE             1          

Stats: Total Time 15
Stats: CPU Busy 8 (53.33%)
Stats: IO Busy  10 (66.67%)

(base) tianyu@Tianyus-MBP Downloads % python3 process-run.py -s 1 -l 3:50,3:50 -c -p -S SWITCH_ON_IO

Time        PID: 0        PID: 1           CPU           IOs
  1        RUN:cpu         READY             1          
  2         RUN:io         READY             1          
  3        BLOCKED       RUN:cpu             1             1
  4        BLOCKED       RUN:cpu             1             1
  5        BLOCKED       RUN:cpu             1             1
  6        BLOCKED          DONE                           1
  7        BLOCKED          DONE                           1
  8*   RUN:io_done          DONE             1          
  9         RUN:io          DONE             1          
 10        BLOCKED          DONE                           1
 11        BLOCKED          DONE                           1
 12        BLOCKED          DONE                           1
 13        BLOCKED          DONE                           1
 14        BLOCKED          DONE                           1
 15*   RUN:io_done          DONE             1          

Stats: Total Time 15
Stats: CPU Busy 8 (53.33%)
Stats: IO Busy  10 (66.67%)

- **What happens when you use the flag -I IO RUN IMMEDIATE versus that flag -I IO RUN LATER? What happens when you use the flag -S SWITCH ON IO versus -S SWITCH ON END?**
- Both IO_RUN_IMMEDIATE and SWITCH_ON_IO produce identical results because there is no significant contention for the CPU, and both processes (one I/O-bound, one CPU-bound) efficiently utilize the CPU and I/O resources. However, in scenarios with more complex workloads or more frequent I/O operations, IO_RUN_IMMEDIATE would likely lead to shorter execution times by prioritizing I/O-completed processes over purely CPU-bound tasks.
