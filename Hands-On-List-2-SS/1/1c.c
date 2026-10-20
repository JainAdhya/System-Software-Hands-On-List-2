
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

/* Signal handler for ITIMER_PROF */
void timer_handler(int signum)
{
    write(STDOUT_FILENO,
          "ITIMER_PROF: Timer expired!\n", 28);
}

int main()
{
    struct itimerval timer;
    volatile unsigned long counter = 0;

    /* Register the signal handler */
    if (signal(SIGPROF, timer_handler) == SIG_ERR)
    {
        perror("signal");
        return 1;
    }

    /* Initial expiration: 10 seconds and 10 microseconds */
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    /* Repeat every 10 seconds and 10 microseconds */
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    /* Start the profiling timer */
    if (setitimer(ITIMER_PROF, &timer, NULL) == -1)
    {
        perror("setitimer");
        return 1;
    }

    printf("ITIMER_PROF timer started.\n");
    printf("Executing CPU instructions...\n");
    fflush(stdout);

    /* Consume CPU time so the timer can expire */
    while (1)
    {
        counter++;
    }

    return 0;
}

/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/1$ ./1c
ITIMER_PROF timer started.
Executing CPU instructions...
ITIMER_PROF: Timer expired!
ITIMER_PROF: Timer expired!
ITIMER_PROF: Timer expired!
ITIMER_PROF: Timer expired!
ITIMER_PROF: Timer expired!
ITIMER_PROF: Timer expired!
^C

*/
