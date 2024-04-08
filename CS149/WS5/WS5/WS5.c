#include <stdio.h>
#include <unistd.h>

int main() {
    for(int i = 0; i < 4; i++) if(fork() == 0) { printf("hello world from PID %d!\n", getpid()); return 0; }
    return 0;
}