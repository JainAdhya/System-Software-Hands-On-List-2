
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct message
{
    long mtype;
    char mtext[100];
};

int main()
{
    key_t key;
    int msgid;
    struct message msg;

    // Generate the message queue key
    key = ftok(".", 'A');

    if (key == -1)
    {
        perror("ftok");
        return 1;
    }

    // Create or access the message queue
    msgid = msgget(key, IPC_CREAT | 0666);

    if (msgid == -1)
    {
        perror("msgget");
        return 1;
    }

    // Prepare the message
    msg.mtype = 1;

    printf("Enter a message: ");
    if (fgets(msg.mtext, sizeof(msg.mtext), stdin) == NULL)
        return 1;

    msg.mtext[strcspn(msg.mtext, "\n")] = '\0';

    // Send the message to the queue
    if (msgsnd(msgid, &msg, strlen(msg.mtext) + 1, 0) == -1)
    {
        perror("msgsnd");
        return 1;
    }

    printf("Message sent successfully!\n");
    printf("Message Queue ID: %d\n", msgid);

    return 0;
}

/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/26$ ./26
Enter a message: Hello from sender
Message sent successfully!
Message Queue ID: 2
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/26$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages
0x41309d05 0          adhya      666        0            0
0x41309d08 1          adhya      666        0            0
0x41309d0b 2          adhya      666        18           1

*/
