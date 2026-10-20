
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigsegv(int sig)
{
    write(STDOUT_FILENO, "SIGSEGV caught!\n", 16);
}

int main()
{
    struct sigaction sa;

    sa.sa_handler = handle_sigsegv;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGSEGV, &sa, NULL);

    printf("Generating SIGSEGV...\n");
    raise(SIGSEGV);

    printf("Program continues after catching SIGSEGV.\n");

    return 0;
}

/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS$ ./10a
Generating SIGSEGV...
SIGSEGV caught!
Program continues after catching SIGSEGV.

*/
