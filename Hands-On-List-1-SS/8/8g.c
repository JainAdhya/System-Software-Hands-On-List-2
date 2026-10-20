
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handler(int signum)
{
    write(STDOUT_FILENO, "SIGPROF caught!\n", 16);
    _exit(0);
}

int main()
{
    struct itimerval timer;
    volatile unsigned long counter = 0;

    signal(SIGPROF, handler);

    timer.it_value.tv_sec = 3;
    timer.it_value.tv_usec = 0;

    /* One-shot timer */
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_PROF, &timer, NULL) == -1)
    {
        perror("setitimer");
        return 1;
    }

    printf("ITIMER_PROF set for 3 CPU seconds...\n");
    fflush(stdout);

    /* Consume CPU time */
    while (1)
    {
        counter++;
    }

    return 0;
}


/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/8$ ./8g
ITIMER_PROF set for 3 CPU seconds...
SIGPROF caught!

*/
