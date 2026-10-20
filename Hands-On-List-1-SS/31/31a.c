
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main()
{
    key_t key;
    int semid;
    union semun arg;

    key = ftok(".", 'A');

    if (key == -1)
    {
        perror("ftok");
        return 1;
    }

    // Create a semaphore set containing one semaphore
    semid = semget(key, 1, IPC_CREAT | 0666);

    if (semid == -1)
    {
        perror("semget");
        return 1;
    }

    // Initialize the binary semaphore to 1
    arg.val = 1;

    if (semctl(semid, 0, SETVAL, arg) == -1)
    {
        perror("semctl");
        return 1;
    }

    printf("Binary semaphore created successfully.\n");
    printf("Semaphore ID: %d\n", semid);
    printf("Initial value: %d\n", arg.val);

    return 0;
}


/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/31$ gcc 31a.c -o 31a
./31a
Binary semaphore created successfully.
Semaphore ID: 0
Initial value: 1

*/
