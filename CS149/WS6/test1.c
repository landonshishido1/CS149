#include "apue.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int
main(void)
{
    pid_t   pid;

    printf("Starting program. Parent PID: %ld\n", (long)getpid());

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid != 0) {        /* parent */
        printf("Parent PID: %ld\n", (long)getpid());
        sleep(2);
        exit(2);                /* terminate with exit status 2 */
    }

    printf("First child PID: %ld\n", (long)getpid());

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid != 0) {        /* first child */
        printf("First child PID: %ld\n", (long)getpid());
        sleep(4);
        abort();                /* terminate with core dump */
    }

    printf("Second child PID: %ld\n", (long)getpid());

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid != 0) {        /* second child */
        printf("Second child PID: %ld\n", (long)getpid());
        execl("/bin/dd", "dd", "if=/etc/passwd", "of=/dev/null", NULL);
        exit(7);                /* shouldn't get here */
    }

    printf("Third child PID: %ld\n", (long)getpid());

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid != 0) {        /* third child */
        printf("Third child PID: %ld\n", (long)getpid());
        sleep(8);
        exit(0);                /* normal exit */
    }

    printf("Fourth child PID: %ld\n", (long)getpid());

    sleep(6);                    /* fourth child */
    kill(getpid(), SIGKILL);     /* terminate w/signal, no core dump */
    exit(6);                     /* shouldn't get here */
}
