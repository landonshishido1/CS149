#  Assignment 6 SP24
- Author names: Landon Shishido
- Author emails: landon.shishido@sjsu.edu
- Last modified date: 5/6/2024
- Creation date: 5/4/2024

## To Run:
1) Compile countnames_threaded.c with command "gcc -D_REENTRANT -pthread -o countnames_threaded countnames_threaded.c -Wall -Werror"
2) Can now test using test cases provided in /test directory, examples are below

## Test Cases

"time ./countnames_threaded test/names1.txt test/names2.txt "

Run 1: 0.007s
Run 2: 0.008s
Run 3: 0.004s

Average Runtime: 0.006s


### 


