
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_sigfpe(int sig)
{
    write(STDOUT_FILENO, "SIGFPE caught!\n", 15);
}

int main()
{
    struct sigaction sa;

    sa.sa_handler = handle_sigfpe;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGFPE, &sa, NULL);

    printf("Generating SIGFPE...\n");
    raise(SIGFPE);

    printf("Program continues after catching SIGFPE.\n");

    return 0;
}

/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS$ ./10c
Generating SIGFPE...
SIGFPE caught!
Program continues after catching SIGFPE.

*/
