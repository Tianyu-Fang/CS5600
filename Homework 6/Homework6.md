## Homework6

# Chapter 18

**Question 1**
page-table size = address space / page size
Big pages will cause waste

**Question 2**
More pages are valid.

**Question 3**
The first and third are unrealistic, the first is too small and the third is too big.

**Question 4**
```
$ ./paging-linear-translate.py -a 65k -v -c
ARG address space size 65k
ARG phys mem size 64k
Error: physical memory size must be GREATER than address space size (for this simulation)

$ ./paging-linear-translate.py -a 0 -v -c
ARG address space size 0
Error: must specify a non-zero address-space size.

$  ./paging-linear-translate.py -p 0 -v -c
ARG phys mem size 0
Error: must specify a non-zero physical memory size.

$ ./paging-linear-translate.py -P 0 -v -c
Traceback (most recent call last):
File "./paging-linear-translate.py", line 85, in <module>
    mustbemultipleof(asize, pagesize, 'address space must be a multiple of the pagesize')
File "./paging-linear-translate.py", line 14, in mustbemultipleof
    if (int(float(bignum)/float(num)) != (int(bignum) / int(num))):
ZeroDivisionError: float division by zero

$ ./paging-linear-translate.py -P 32k -v -c
Traceback (most recent call last):
File "./paging-linear-translate.py", line 174, in <module>
    if pt[vpn] < 0:
IndexError: array index out of range
```

# Chapter 19

**Question 1**
CLOCK_PROCESS_CPUTIME_ID has resolution of 1 nanosecond on Linux, 1000 nanoseconds on macOS.

**Question 5**
Using gcc's optimize option gcc -O0 to disable optimization. This is the default setting.

**Question 6**
Use sched_setaffinity(2), pthread_setaffinity_np(3), taskset(1) or sudo systemd-run -p AllowedCPUs=0 ./tlb.out on Linux, cpuset_setaffinity(2) or cpuset(1) on FreeBSD.

Or use hwloc-bind package:0.pu:0 -- ./tlb.out.

**Question 7**
Use calloc(3) to initialize array then measure time.
