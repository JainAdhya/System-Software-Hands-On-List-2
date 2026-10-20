
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

    // Open fifo1 for writing and fifo2 for reading
    fd1 = open("fifo1", O_WRONLY);
    fd2 = open("fifo2", O_RDONLY);

    printf("Program 1: Enter message: ");
    fgets(message, sizeof(message), stdin);

    write(fd1, message, strlen(message) + 1);

    read(fd2, message, sizeof(message));
    printf("Program 1 received: %s", message);

    close(fd1);
    close(fd2);

    return 0;
}


/* Output:

Terminal 1:
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/21$ ./program1
Program 1: Enter message: Hello, how are you?
Program 1 received: I am fine, thank you <3

Terminal 2:
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/21$ ./program2
Program 2 received: Hello, how are you?
Program 2: Enter reply: I am fine, thank you <3

*/
