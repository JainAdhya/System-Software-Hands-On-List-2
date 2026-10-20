
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main()
{
    struct rlimit limit;

    /* Set the soft and hard limits */
    limit.rlim_cur = 50;
    limit.rlim_max = 100;

    /* Set the maximum number of open file descriptors */
    if (setrlimit(RLIMIT_NOFILE, &limit) == -1)
    {
        perror("setrlimit");
        return 1;
    }

    printf("Open file limit set successfully.\n");

    /* Retrieve the updated limits */
    if (getrlimit(RLIMIT_NOFILE, &limit) == -1)
    {
        perror("getrlimit");
        return 1;
    }

    printf("Soft limit: %llu\n",
           (unsigned long long)limit.rlim_cur);

    printf("Hard limit: %llu\n",
           (unsigned long long)limit.rlim_max);

    return 0;
}


/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/3$ ./3
Open file limit set successfully.
Soft limit: 50
Hard limit: 100

*/
