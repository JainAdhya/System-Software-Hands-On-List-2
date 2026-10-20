
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

void handler(int sig)
{
    printf("SIGSTOP caught!\n");
}

int main()
{
    // Attempt to register a handler for SIGSTOP
    if (signal(SIGSTOP, handler) == SIG_ERR)
    {
        perror("Cannot catch SIGSTOP");
    }

    printf("Receiver process PID: %d\n", getpid());
    printf("Waiting for signals...\n");
    fflush(stdout);

    while (1)
    {
        pause();
    }

    return 0;
}

/* Output:
 
Terminal 1

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/13$ ./receiver
Cannot catch SIGSTOP: Invalid argument
Receiver process PID: 4646
Waiting for signals...

[2]+  Stopped                    ./receiver

*/
