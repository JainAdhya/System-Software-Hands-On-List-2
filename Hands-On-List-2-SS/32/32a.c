
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
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
    int shmid = shmget(IPC_PRIVATE, sizeof(int),
                       IPC_CREAT | 0666);
    int semid = semget(IPC_PRIVATE, 1,
                       IPC_CREAT | 0666);

    if (shmid == -1 || semid == -1) {
        perror("IPC creation failed");
        exit(1);
    }

    int *ticket = (int *)shmat(shmid, NULL, 0);

    if (ticket == (void *)-1) {
        perror("shmat");
        exit(1);
    }

    *ticket = 100;

    union semun arg;
    arg.val = 1;

    if (semctl(semid, 0, SETVAL, arg) == -1) {
        perror("semctl");
        exit(1);
    }

    for (int i = 0; i < 5; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            wait_sem(semid);

            int my_ticket = *ticket;
            *ticket = *ticket + 1;

            printf("Process %d received ticket %d\n",
                   getpid(), my_ticket);

            signal_sem(semid);
            shmdt(ticket);
            exit(0);
        }
    }

    for (int i = 0; i < 5; i++)
        wait(NULL);

    printf("Next ticket number: %d\n", *ticket);

    shmdt(ticket);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);

    return 0;
}

/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/32$ gcc 32a.c -o 32a
./32a
Process 8837 received ticket 100
Process 8838 received ticket 101
Process 8839 received ticket 102
Process 8840 received ticket 103
Process 8841 received ticket 104
Next ticket number: 105

*/
