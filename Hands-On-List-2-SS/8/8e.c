
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handler(int signum)
{
    write(STDOUT_FILENO, "SIGALRM caught!\n", 16);
    _exit(0);
}

int main()
{
    struct itimerval timer;

    signal(SIGALRM, handler);

    timer.it_value.tv_sec = 5;
    timer.it_value.tv_usec = 0;

    /* One-shot timer */
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    if (setitimer(ITIMER_REAL, &timer, NULL) == -1)
    {
        perror("setitimer");
        return 1;
    }

    printf("ITIMER_REAL set for 5 seconds...\n");
    fflush(stdout);

    while (1)
    {
        pause();
    }

    return 0;
}

/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/8$ ./8e
ITIMER_REAL set for 5 seconds...
SIGALRM caught!

*/
