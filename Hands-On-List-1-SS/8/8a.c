
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum)
{
    write(STDOUT_FILENO, "SIGSEGV caught!\n", 16);
    _exit(0);
}

int main()
{
    signal(SIGSEGV, handler);

    printf("Generating SIGSEGV...\n");
    fflush(stdout);

    raise(SIGSEGV);

    return 0;
}

/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/8$ ./8a
Generating SIGSEGV...
SIGSEGV caught!

*/
