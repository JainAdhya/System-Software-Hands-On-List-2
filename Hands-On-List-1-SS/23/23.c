
#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    long max_files;
    int fd[2];
    int pipe_size;

    // Find the maximum number of open file descriptors
    max_files = sysconf(_SC_OPEN_MAX);

    if (max_files == -1)
    {
        perror("sysconf");
    }
    else
    {
        printf("Maximum number of open file descriptors: %ld\n",
               max_files);
    }

    // Create a pipe
    if (pipe(fd) == -1)
    {
        perror("pipe");
        return 1;
    }

    // Find the pipe capacity
    pipe_size = fcntl(fd[0], F_GETPIPE_SZ);

    if (pipe_size == -1)
    {
        perror("fcntl");
    }
    else
    {
        printf("Size of pipe (circular buffer): %d bytes\n",
               pipe_size);
    }

    close(fd[0]);
    close(fd[1]);

    return 0;
}


/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/23$ ./23
Maximum number of open file descriptors: 10240
Size of pipe (circular buffer): 65536 bytes

*/
