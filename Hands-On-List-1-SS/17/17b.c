
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    pipe(fd);

    if (fork() == 0)
    {
        // Child 1: execute ls -l
        close(fd[0]);

        dup2(fd[1], STDOUT_FILENO);

        close(fd[1]);
        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp ls");
        exit(1);
    }

    if (fork() == 0)
    {
        // Child 2: execute wc
        close(fd[1]);

        dup2(fd[0], STDIN_FILENO);

        close(fd[0]);
        execlp("wc", "wc", (char *)NULL);
        perror("execlp wc");
        exit(1);
    }

    // Parent process
    close(fd[0]);
    close(fd[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}

/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/17$ ./17b
      5      38     205

*/
