
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handler(int signum)
{
    write(STDOUT_FILENO, "SIGVTALRM caught!\n", 18);
    _exit(0);
}

int main()
{
    struct itimerval timer;
    volatile unsigned long counter = 0;

    signal(SIGVTALRM, handler);

    timer.it_value.tv_sec = 3;
    timer.it_value.tv_usec = 0;

    /* One-shot timer */
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1)
    {
        perror("setitimer");
        return 1;
    }

    printf("ITIMER_VIRTUAL set for 3 CPU seconds...\n");
    fflush(stdout);

    /* Consume user-mode CPU time */
    while (1)
    {
        counter++;
    }

    return 0;
}


/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/8$ ./8f
ITIMER_VIRTUAL set for 3 CPU seconds...
SIGVTALRM caught!

*/
