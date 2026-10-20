
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    int msgid = 5;

    if (msgctl(msgid, IPC_RMID, NULL) == -1)
    {
        perror("msgctl IPC_RMID");
        return 1;
    }

    printf("Message queue removed successfully!\n");

    return 0;
}


/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/29$ ipcs -q

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages
0x41309d05 0          adhya      666        0            0
0x41309d08 1          adhya      666        0            0
0x41309d0b 2          adhya      666        18           1
0x41309d12 5          adhya      644        0            0

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/29$ ./29
Message queue removed successfully!

*/
