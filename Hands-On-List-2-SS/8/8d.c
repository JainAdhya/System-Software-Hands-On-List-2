
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum)
{
    write(STDOUT_FILENO, "SIGALRM caught!\n", 16);
    _exit(0);
}

int main()
{
    signal(SIGALRM, handler);

    printf("Alarm set for 5 seconds...\n");
    fflush(stdout);

    alarm(5);

    while (1)
    {
        pause();
    }

    return 0;
}

/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/8$ ./8d
Alarm set for 5 seconds...
SIGALRM caught!

*/
