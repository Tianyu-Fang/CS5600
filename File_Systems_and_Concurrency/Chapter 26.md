# Chapter 26

**Question 1**
```
$ ./x86.py -p loop.s -t 1 -i 100 -R dx -c
dx          Thread 0         
 0   
-1   1000 sub  $1,%dx
-1   1001 test $0,%dx
-1   1002 jgte .top
-1   1003 halt
```

**Question 2**
3, no, no

**Question 3**
no

**Question 4**
```
$ ./x86.py -p looping-race-nolock.s -t 1 -M 2000 -c
2000          Thread 0         
0   
0   1000 mov 2000, %ax
0   1001 add $1, %ax
1   1002 mov %ax, 2000
1   1003 sub  $1, %bx
1   1004 test $0, %bx
1   1005 jgt .top
1   1006 halt
```

**Question 5**
Because bx is initialized to 3. 

6.

**Question 6**
Whether increased ax is saved to value before get reset.

**Question 7**
1, 1, 2, intervals >= 3

**Question 8**
intervals >= 597, == 3 * x (x = 1, 2, 3...)

**Question 9**
Thread 0 sets memory 2000 to 1 then halt. Thread 1 keeps running in a loop until memory 2000 is 1.

**Question 10**
no

