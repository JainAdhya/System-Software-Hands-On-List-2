
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <PID>\n", argv[0]);
        return 1;
    }

    pid_t pid = (pid_t)atoi(argv[1]);

    if (kill(pid, SIGSTOP) == -1)
    {
        perror("kill failed");
        return 1;
    }

    printf("SIGSTOP sent to process %d successfully.\n", pid);

    return 0;
}


/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/13$ ./sender 4646
SIGSTOP sent to process 4646 successfully.
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/13$ ps -o pid,stat,cmd -p 4646
    PID STAT CMD
   4646 T    ./receiver

*/
