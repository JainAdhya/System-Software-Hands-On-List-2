
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

void print_time(const char *label, time_t t)
{
    if (t == 0)
        printf("%s: Not available yet\n", label);
    else
        printf("%s: %s", label, ctime(&t));
}

int main()
{
    key_t key;
    int msgid;
    struct msqid_ds info;

    // Generate the message queue key
    key = ftok(".", 'A');

    if (key == -1)
    {
        perror("ftok");
        return 1;
    }

    // Create the queue if it does not already exist
    msgid = msgget(key, IPC_CREAT | 0666);

    if (msgid == -1)
    {
        perror("msgget");
        return 1;
    }

    // Get information about the message queue
    if (msgctl(msgid, IPC_STAT, &info) == -1)
    {
        perror("msgctl");
        return 1;
    }

    printf("Message Queue Key: %d\n", (int)key);
    printf("Message Queue ID: %d\n", msgid);

    printf("\n--- Message Queue Information ---\n");

    // a. Access permission
    printf("Access Permission: %o\n",
           (unsigned int)(info.msg_perm.mode & 0777));

    // b. User ID and Group ID
    printf("UID: %u\n", (unsigned int)info.msg_perm.uid);
    printf("GID: %u\n", (unsigned int)info.msg_perm.gid);

    // c. Time of last message sent and received
    print_time("Last Message Sent", info.msg_stime);
    print_time("Last Message Received", info.msg_rtime);

    // d. Time of last change in the queue
    print_time("Last Change in Queue", info.msg_ctime);

    // e. Current size of the queue
    printf("Current Queue Size: %lu bytes\n",
           (unsigned long)info.msg_cbytes);

    // f. Number of messages in the queue
    printf("Number of Messages: %lu\n",
           (unsigned long)info.msg_qnum);

    // g. Maximum number of bytes allowed
    printf("Maximum Bytes Allowed: %lu bytes\n",
           (unsigned long)info.msg_qbytes);

    // h. PIDs of last sender and receiver
    printf("PID of Last msgsnd: %d\n", (int)info.msg_lspid);
    printf("PID of Last msgrcv: %d\n", (int)info.msg_lrpid);

    return 0;
}

/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/25$ ./25
Message Queue Key: 1093704968
Message Queue ID: 1

--- Message Queue Information ---
Access Permission: 666
UID: 1000
GID: 1000
Last Message Sent: Not available yet
Last Message Received: Not available yet
Last Change in Queue: Tue Oct 20 11:14:09 2026
Current Queue Size: 0 bytes
Number of Messages: 0
Maximum Bytes Allowed: 16384 bytes
PID of Last msgsnd: 0
PID of Last msgrcv: 0

*/
