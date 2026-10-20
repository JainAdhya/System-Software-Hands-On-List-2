
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/wait.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void wait_sem(int semid) {
    struct sembuf op = {0, -1, 0};
    semop(semid, &op, 1);
}

void signal_sem(int semid) {
    struct sembuf op = {0, 1, 0};
    semop(semid, &op, 1);
}

int main() {
    int semid = semget(IPC_PRIVATE, 1,
                       IPC_CREAT | 0666);

    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    union semun arg;
    arg.val = 2;

    if (semctl(semid, 0, SETVAL, arg) == -1) {
        perror("semctl");
        exit(1);
    }

    printf("Two resources are available.\n");

    for (int i = 1; i <= 5; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            wait_sem(semid);

            printf("Process %d acquired a resource.\n",
                   getpid());
            sleep(2);
            printf("Process %d released a resource.\n",
                   getpid());

            signal_sem(semid);
            exit(0);
        }
    }

    for (int i = 0; i < 5; i++)
        wait(NULL);

    semctl(semid, 0, IPC_RMID);
    printf("All processes completed.\n");

    return 0;
}

/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/32$ gcc 32c.c -o 32c
./32c
Two resources are available.
Process 8944 acquired a resource.
Process 8945 acquired a resource.
Process 8944 released a resource.
Process 8945 released a resource.
Process 8946 acquired a resource.
Process 8947 acquired a resource.
Process 8946 released a resource.
Process 8947 released a resource.
Process 8948 acquired a resource.
Process 8948 released a resource.
All processes completed.

*/
