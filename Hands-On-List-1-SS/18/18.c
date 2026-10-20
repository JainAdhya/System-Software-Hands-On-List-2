#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int p1[2], p2[2];
    pipe(p1); pipe(p2);

    if(fork() == 0){          // ls -l
        dup2(p1[1], 1); close(p1[0]); close(p1[1]);
        close(p2[0]); close(p2[1]);
        execlp("ls", "ls", "-l", NULL);
        perror("ls"); exit(1);
    }

    if(fork() == 0){          // grep ^d
        dup2(p1[0], 0); close(p1[0]); close(p1[1]);
        dup2(p2[1], 1); close(p2[0]); close(p2[1]);
        execlp("grep", "grep", "^d", NULL);
        perror("grep"); exit(1);
    }

    // parent: wc
    close(p1[0]); close(p1[1]);
    dup2(p2[0], 0); close(p2[0]); close(p2[1]);
    execlp("wc", "wc", NULL);
    perror("wc"); exit(1);
}


/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/18$ ./18
      2      18     100

*/
