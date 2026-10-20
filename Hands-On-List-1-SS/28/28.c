
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    key_t key;
    int msgid;
    struct msqid_ds info;

    // Generate the message queue key
    key = ftok("msgqueuefile", 65);

    if (key == -1)
    {
        perror("ftok");
        return 1;
    }

    // Access the existing message queue
    msgid = msgget(key, IPC_CREAT | 0666);

    if (msgid == -1)
    {
        perror("msgget");
        return 1;
    }

    // Get the current queue information
    if (msgctl(msgid, IPC_STAT, &info) == -1)
    {
        perror("msgctl IPC_STAT");
        return 1;
    }

    printf("Old permissions: %o\n",
           (unsigned int)(info.msg_perm.mode & 0777));

    // Change permissions to 0644
    info.msg_perm.mode = (info.msg_perm.mode & ~0777) | 0644;

    // Apply the updated permissions
    if (msgctl(msgid, IPC_SET, &info) == -1)
    {
        perror("msgctl IPC_SET");
        return 1;
    }

    // Verify the new permissions
    if (msgctl(msgid, IPC_STAT, &info) == -1)
    {
        perror("msgctl IPC_STAT");
        return 1;
    }

    printf("New permissions: %o\n",
           (unsigned int)(info.msg_perm.mode & 0777));

    return 0;
}


/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/28$ ./28
Old permissions: 666
New permissions: 644

*/
