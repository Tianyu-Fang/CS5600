# CS5600 Homework 3

# Homework 3
# Chapter 8
## Question 1
$ ./mlfq.py -s 0 -n 2 -j 2 -m 20 -M 0 -c
$ ./mlfq.py -s 1 -n 2 -j 2 -m 20 -M 0 -c

## Question 2
// Figure 8.2 Long-running Job Over Time
$ ./mlfq.py -n 3 -q 10 -l 0,200,0 -c

// Figure 8.3 Along Came An Interactive Job
$ ./mlfq.py -n 3 -q 10 -l 0,180,0:100,20,0 -c

// Figure 8.4 A Mixed I/O-intensive and CPU-intensive Workload
$ ./mlfq.py -n 3 -q 10 -l 0,175,0:50,25,1 -i 5 -S -c

// Figure 8.5 without priority boost
$ ./mlfq.py -n 3 -q 10 -l 0,120,0:100,50,1:100,50,1 -i 1 -S -c

// Figure 8.5 with priority boost
$ ./mlfq.py -n 3 -q 10 -l 0,120,0:100,50,1:100,50,1 -i 1 -S -B 50 -c

// Figure 8.6 without gaming tolerance
$ ./mlfq.py -n 3 -q 10 -i 1 -S -l 0,200,0:80,100,9 -c

// Figure 8.6 with gaming tolerance
$ ./mlfq.py -n 3 -q 10 -i 1 -l 0,200,0:80,100,9 -c

// Figure 8.7 Lower Priority, Longer Quanta
$ ./mlfq.py -n 3 -a 2 -Q 10,20,40 -l 0,200,0:0,200,0 -c

## Question 3
Jobs on the same queue are time-sliced, so the answer is to have only one queue: ./mlfq.py -n 1 -M 0 -s 23 -c

## Question 4
First, set the I/O time to 1 with -i, then ensure that CPU hog calls an I/O operation on the 99th click of a 100 click quantum length. Also, include the -I flag to ensure the CPU hog gets back control when the I/O request finishes: ./mlfq.py -S -i 1 -l 0,297,99:0,60,0 -q 100 -n 3 -I -c

## Question 5
If a new 10ms-long job arrives every 10ms - like pictured in Figure 8.5 (left), boosting every 200 ticks ensures the long process will run 10/200 CPU ticks = 5%.

## Question 6
$ ./mlfq.py -n 2 -q 10 -l 0,50,0:0,50,11 -i 1 -S -c
$ ./mlfq.py -n 2 -q 10 -l 0,50,0:0,50,11 -i 1 -S -I -c

# Chapter 9

## Question 1
$ ./lottery.py -s 1 -j 3 -c 

$ ./lottery.py -s 2 -j 3 -c 

$ ./lottery.py -s 3 -j 3 -c  

## Question 2
$ ./lottery.py -l 10:1,10:100 -c
Job 1 will have more opportunities to run.
1/100
Not fair for the lower tickets jobs.

## Question 3
$ ./lottery.py -s 0 -l 100:100,100:100 -c
U = 192/200 = 0.96

$ ./lottery.py -s 1 -l 100:100,100:100 -c
U = 192/200 = 0.96

$ ./lottery.py -s 2 -l 100:100,100:100 -c
U = 190/200 = 0.95

$ ./lottery.py -s 3 -l 100:100,100:100 -c
U = 196/200 = 0.98

## Question 4
$ ./plot_quantum.py 

## Question 5
$ ./plot.py
check turnaround time: $ ./plot_stride.py



