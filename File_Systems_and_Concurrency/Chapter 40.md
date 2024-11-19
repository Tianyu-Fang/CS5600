# Chapter 40 Homework


**Question 1**
```
vsfs.py -n 6 -s 17
vsfs.py -n 6 -s 18
vsfs.py -n 6 -s 19
vsfs.py -n 6 -s 20
```


**Question 2**
The first available block.

**Question 3**
```
$ ./vsfs.py -d 2 -n 100 -p -c -s 21
```

Some empty files and links in the root directory.

`makedir()` and `write()` fail, but shouldn't. The last data block seems can't be used.

**Question 4**
```
$ ./vsfs.py -i 2 -n 100 -p -c -s 21
```
All operations except `unlink()` will fail. Only the first inode is available.

Change to three inodes ends up with an empty directory or a small file.



