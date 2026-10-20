
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum)
{
    write(STDOUT_FILENO, "\nSIGINT caught!\n", 16);
}

int main()
{
    signal(SIGINT, handler);

    printf("Press Ctrl+C to generate SIGINT.\n");

    while (1)
    {
        pause();
    }

    return 0;
}

/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/8$ ./8b
Press Ctrl+C to generate SIGINT.
^C
SIGINT caught!
^C
SIGINT caught!
^C
SIGINT caught!
^\Quit                       ./8b

*/
