
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum)
{
    write(STDOUT_FILENO, "SIGFPE caught!\n", 15);
    _exit(0);
}

int main()
{
    signal(SIGFPE, handler);

    printf("Generating SIGFPE...\n");
    fflush(stdout);

    raise(SIGFPE);

    return 0;
}

/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/8$ ./8c
Generating SIGFPE...
SIGFPE caught!

*/
