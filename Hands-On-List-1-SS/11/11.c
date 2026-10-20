
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    struct sigaction sa;

    // Ignore SIGINT
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);

    printf("SIGINT is ignored. Press Ctrl+C for 10 seconds.\n");
    sleep(10);

    // Restore the default action of SIGINT
    sa.sa_handler = SIG_DFL;
    sigaction(SIGINT, &sa, NULL);

    printf("\nDefault action of SIGINT restored.\n");
    printf("Press Ctrl+C again to terminate the program.\n");

    while (1)
    {
        pause();
    }

    return 0;
}

/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/11$ ./11
SIGINT is ignored. Press Ctrl+C for 10 seconds.
^C
^C
^C
^C

Default action of SIGINT restored.
Press Ctrl+C again to terminate the program.
^C

*/
