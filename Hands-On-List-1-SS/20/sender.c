
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd;
    char message[100];

    // Create FIFO if it does not already exist
    if (mkfifo("myfifo", 0666) == -1)
    {
        // FIFO may already exist
    }

    printf("Enter a message to send: ");
    fgets(message, sizeof(message), stdin);

    // Open FIFO for writing
    fd = open("myfifo", O_WRONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    // Write message into FIFO
    write(fd, message, strlen(message) + 1);

    printf("Message sent successfully.\n");

    close(fd);

    return 0;
}

/* Output:

Terminal 1:
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/20$ ./rece>
Message received: Hello How are you?

Terminal 2:
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/20$ ./send>
Enter a message to send: Hello How are you?
Message sent successfully.


*/
