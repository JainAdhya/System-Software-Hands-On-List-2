
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main()
{
    int shmid;
    char *ptr;
    const int SIZE = 1024;
    pid_t pid;
    int status;

    // Create shared memory
    shmid = shmget(IPC_PRIVATE, SIZE, IPC_CREAT | 0666);

    if (shmid == -1)
    {
        perror("shmget");
        return 1;
    }

    printf("Shared memory created successfully.\n");
    printf("Shared Memory ID: %d\n", shmid);

    // a. Attach with read/write permission and write data
    ptr = (char *)shmat(shmid, NULL, 0);

    if (ptr == (char *)-1)
    {
        perror("shmat");
        shmctl(shmid, IPC_RMID, NULL);
        return 1;
    }

    strcpy(ptr, "Hello from shared memory!");
    printf("Data written: %s\n", ptr);

    // c. Detach shared memory
    if (shmdt(ptr) == -1)
    {
        perror("shmdt");
        shmctl(shmid, IPC_RMID, NULL);
        return 1;
    }

    printf("Shared memory detached.\n");

    // b. Attach read-only in a child process and test overwriting
    pid = fork();

    if (pid == -1)
    {
        perror("fork");
        shmctl(shmid, IPC_RMID, NULL);
        return 1;
    }

    if (pid == 0)
    {
        char *read_ptr;

        read_ptr = (char *)shmat(shmid, NULL, SHM_RDONLY);

        if (read_ptr == (char *)-1)
        {
            perror("shmat read-only");
            _exit(1);
        }

        printf("Read-only attachment: %s\n", read_ptr);
        fflush(stdout);

        // Attempt to overwrite read-only shared memory
        ((volatile char *)read_ptr)[0] = 'X';

        // Reached only if the write unexpectedly succeeds
        printf("Overwrite was possible.\n");
        shmdt(read_ptr);
        _exit(0);
    }

    // Parent checks the result of the overwrite attempt
    waitpid(pid, &status, 0);

    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGSEGV)
        printf("Overwrite not possible: read-only memory caused SIGSEGV.\n");
    else if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        printf("Overwrite was possible.\n");
    else
        printf("Read-only overwrite test failed.\n");

    // d. Remove shared memory
    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("shmctl IPC_RMID");
        return 1;
    }

    printf("Shared memory removed successfully.\n");

    return 0;
}


/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/30$ gcc 30.c -o 30
./30
Shared memory created successfully.
Shared Memory ID: 0
Data written: Hello from shared memory!
Shared memory detached.
Read-only attachment: Hello from shared memory!
Overwrite not possible: read-only memory caused SIGSEGV.
Shared memory removed successfully.

*/
