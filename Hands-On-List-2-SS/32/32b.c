
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

    int *counter = (int *)shmat(shmid, NULL, 0);

    if (counter == (void *)-1) {
        perror("shmat");
        exit(1);
    }

    *counter = 0;

    union semun arg;
    arg.val = 1;
    semctl(semid, 0, SETVAL, arg);

    for (int i = 0; i < 4; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            for (int j = 0; j < 10000; j++) {
                wait_sem(semid);
                (*counter)++;
                signal_sem(semid);
            }

            shmdt(counter);
            exit(0);
        }
    }

    for (int i = 0; i < 4; i++)
        wait(NULL);

    printf("Final counter value: %d\n", *counter);
    printf("Expected counter value: 40000\n");

    shmdt(counter);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);

    return 0;
}


/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/32$ gcc 32b.c -o 32b
./32b
Final counter value: 40000
Expected counter value: 40000

*/
