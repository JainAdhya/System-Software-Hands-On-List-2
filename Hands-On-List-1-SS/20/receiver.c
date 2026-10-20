
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    int fd;
    char message[100];

    // Create FIFO if it does not already exist
    if (mkfifo("myfifo", 0666) == -1)
    {
        // FIFO may already exist
    }

    // Open FIFO for reading
    fd = open("myfifo", O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    // Read message from FIFO
    read(fd, message, sizeof(message));

    printf("Message received: %s\n", message);

    close(fd);

    return 0;
}

/* Output:

Terminal 1:
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/20$ ./receiver
Message received: Hello How are you?

Terminal 2:
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/20$ ./sender
Enter a message to send: Hello How are you?
Message sent successfully.


*/
