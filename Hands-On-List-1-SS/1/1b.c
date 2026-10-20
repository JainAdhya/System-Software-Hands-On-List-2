
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

/* Signal handler for ITIMER_VIRTUAL */
void timer_handler(int signum)
{
    write(STDOUT_FILENO,
          "ITIMER_VIRTUAL: Timer expired!\n", 31);
}

int main()
{
    struct itimerval timer;
    volatile unsigned long counter = 0;

    /* Register the signal handler */
    if (signal(SIGVTALRM, timer_handler) == SIG_ERR)
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

    /* Start the virtual timer */
    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1)
    {
        perror("setitimer");
        return 1;
    }

    printf("ITIMER_VIRTUAL timer started.\n");
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

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/1$ ./1b
ITIMER_VIRTUAL timer started.
Executing CPU instructions...
ITIMER_VIRTUAL: Timer expired!
ITIMER_VIRTUAL: Timer expired!
ITIMER_VIRTUAL: Timer expired!
ITIMER_VIRTUAL: Timer expired!
ITIMER_VIRTUAL: Timer expired!
^C

*/
