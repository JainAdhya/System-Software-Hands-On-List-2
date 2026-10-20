
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_sigint(int sig)
{
    write(STDOUT_FILENO, "\nSIGINT caught! Ctrl+C detected.\n", 33);
}

int main()
{
    struct sigaction sa;

    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);

    printf("Press Ctrl+C to generate SIGINT.\n");

    while (1)
    {
        pause();
    }

    return 0;
}

/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS$ ./10b
Press Ctrl+C to generate SIGINT.
^C
SIGINT caught! Ctrl+C detected.
^C
SIGINT caught! Ctrl+C detected.
^C
SIGINT caught! Ctrl+C detected.
^Z
[1]+  Stopped                    ./10b

*/
