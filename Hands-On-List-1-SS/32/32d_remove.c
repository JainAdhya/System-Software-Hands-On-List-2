
#include <stdio.h>
#include <sys/sem.h>
#include <sys/ipc.h>

int main() {
    key_t key = ftok(".", 'D');

    if (key == -1) {
        perror("ftok");
        return 1;
    }

    int semid = semget(key, 1, 0666);

    if (semid == -1) {
        perror("semget");
        return 1;
    }

    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl");
        return 1;
    }

    printf("Semaphore removed successfully.\n");

    return 0;
}

/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/32$ ./32d_create
./32d_remove
Semaphore created successfully.
Semaphore ID: 5
Semaphore removed successfully.
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/32$ ipcs -s

------ Semaphore Arrays --------
key        semid      owner      perms      nsems
0x41309d1e 0          adhya      666        1
0x42309d1e 1          adhya      666        1

*/
