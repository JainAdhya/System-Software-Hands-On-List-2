/*

Name: 1a.c
Author: Adhya Jain
Decsription: Write a separate program (for each time domain) to set a interval timer in 10sec and 10micro second
                a. ITIMER_REAL
                b. ITIMER_VIRTUAL
                c. ITIMER_PROF
Date: 
*/


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

/* Signal handler for ITIMER_REAL */
void timer_handler(int signum)
{
    write(STDOUT_FILENO,
          "ITIMER_REAL: Timer expired!\n", 28);
}

int main()
{
    struct itimerval timer;

    /* Register the signal handler */
    if (signal(SIGALRM, timer_handler) == SIG_ERR)
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

    /* Start the real-time timer */
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1)
    {
        perror("setitimer");
        return 1;
    }

    printf("ITIMER_REAL timer started.\n");
    printf("Waiting for timer expiration...\n");
    fflush(stdout);

    /* Wait for signals */
    while (1)
    {
        pause();
    }

    return 0;
}

/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/1$ ./1a
ITIMER_REAL timer started.
Waiting for timer expiration...
ITIMER_REAL: Timer expired!
ITIMER_REAL: Timer expired!
ITIMER_REAL: Timer expired!
ITIMER_REAL: Timer expired!
^C

*/
