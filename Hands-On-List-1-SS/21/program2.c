
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    int fd1, fd2;
    char message[100];

    mkfifo("fifo1", 0666);
    mkfifo("fifo2", 0666);

    // Open fifo1 for reading and fifo2 for writing
    fd1 = open("fifo1", O_RDONLY);
    fd2 = open("fifo2", O_WRONLY);

    read(fd1, message, sizeof(message));
    printf("Program 2 received: %s", message);

    printf("Program 2: Enter reply: ");
    fgets(message, sizeof(message), stdin);

    write(fd2, message, strlen(message) + 1);

    close(fd1);
    close(fd2);

    return 0;
}

/* Output:

Terminal 1:
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/21$ ./prog>
Program 1: Enter message: Hello, how are you?
Program 1 received: I am fine, thank you <3

Terminal 2:
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/21$ ./prog>
Program 2 received: Hello, how are you?
Program 2: Enter reply: I am fine, thank you <3

*/
