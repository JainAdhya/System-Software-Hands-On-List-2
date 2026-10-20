
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        // Child process
        printf("Child process created.\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());

        sleep(2);

        printf("Child is sending SIGKILL to its parent.\n");
        fflush(stdout);

        // Send SIGKILL to the parent process
        kill(getppid(), SIGKILL);

        sleep(2);

        printf("New Parent PID: %d\n", getppid());
        printf("Child has become an orphan process.\n");
    }
    else
    {
        // Parent process
        printf("Parent process running. PID: %d\n", getpid());
        fflush(stdout);

        while (1)
        {
            pause();
        }
    }

    return 0;
}

/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/12$ ./12
Parent process running. PID: 4405
Child process created.
Child PID: 4406
Parent PID: 4405
Child is sending SIGKILL to its parent.
Killed                     ./12
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/12$ New Parent PID: 490
Child has become an orphan process.
^C

*/
