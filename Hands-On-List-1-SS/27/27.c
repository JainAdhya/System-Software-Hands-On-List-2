#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>

#define MSG_SIZE 100

struct msgbuf{
    long type;
    char text[MSG_SIZE];
};

int main(){
    key_t key;
    int msgid;
    struct msgbuf msg;

    key = ftok("msgqueuefile", 65);
    if(key == -1){
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    msgid = msgget(key, 0666 | IPC_CREAT);
    if(msgid == -1){
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Sending message
    msg.type = 1;
    strcpy(msg.text, "Hello from Adhya");

    if(msgsnd(msgid, &msg, strlen(msg.text) + 1, 0) == -1){
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
    printf("Message sent successfully.\n");


    //a. Received message
    printf("\nReceiving message (blocking mode)...\n");
    if(msgrcv(msgid, &msg, sizeof(msg.text), msg.type, 0) == -1)    //reads message but waits if no message
        perror("msgrcv (blocking)");
    else
        printf("Received (blocking): %s\n", msg.text);


    //b. Trying to receive again (non-blocking mode)
    printf("\nReceiving message (non-blocking mode)...\n");
    int ret = msgrcv(msgid, &msg, sizeof(msg.text), msg.type, IPC_NOWAIT);  //reads message return instantly if no message

    if(ret == -1){
        if(errno == ENOMSG)
            printf("No message available (non-blocking)\n");
        else
            perror("msgrcv (non-blocking)");
    }
    else
        printf("Received (non-blocking): %s\n", msg.text);


    if(msgctl(msgid, IPC_RMID, NULL) == -1)
        perror("msgctl (remove)");
    else
        printf("\nMessage queue deleted successfully.\n");

    return 0;
}


/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/27$ ./27
Message sent successfully.

Receiving message (blocking mode)...
Received (blocking): Hello from Adhya

Receiving message (non-blocking mode)...
No message available (non-blocking)

Message queue deleted successfully.

*/
