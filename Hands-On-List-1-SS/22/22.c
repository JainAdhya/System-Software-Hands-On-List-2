
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/select.h>

int main()
{
    int fd;
    char buffer[100];
    fd_set readfds;
    struct timeval timeout;

    // Create FIFO
    if (mkfifo("myfifo", 0666) == -1)
    {
        // FIFO may already exist
    }

    // Open FIFO in read-only, non-blocking mode
    fd = open("myfifo", O_RDONLY | O_NONBLOCK);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    printf("Waiting for data in FIFO for 10 seconds...\n");

    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    int result = select(fd + 1, &readfds, NULL, NULL, &timeout);

    if (result == -1)
    {
        perror("select");
    }
    else if (result == 0)
    {
        printf("Timeout! No data received within 10 seconds.\n");
    }
    else
    {
        int n = read(fd, buffer, sizeof(buffer) - 1);

        if (n > 0)
        {
            buffer[n] = '\0';
            printf("Data received: %s\n", buffer);
        }
        else
        {
            printf("FIFO became readable, but no data was received.\n");
        }
    }

    close(fd);
    return 0;
}

/* Output:

Try 1:
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/22$ ./22
Waiting for data in FIFO for 10 seconds...
Timeout! No data received within 10 seconds.

Try 2:
Terminal 1:
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/22$ ./22
Waiting for data in FIFO for 10 seconds...
Data received: Hello through FIFO

Termial2:
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/22$ echo "Hello through FIFO" > myfifo

*/
