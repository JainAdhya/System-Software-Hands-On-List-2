
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main()
{
    struct rlimit limit;

    /* Resource names and their corresponding constants */
    int resources[] = {
        RLIMIT_CPU,
        RLIMIT_FSIZE,
        RLIMIT_DATA,
        RLIMIT_STACK,
        RLIMIT_CORE,
        RLIMIT_RSS,
        RLIMIT_NPROC,
        RLIMIT_NOFILE,
        RLIMIT_MEMLOCK,
        RLIMIT_AS
    };

    char *names[] = {
        "CPU time",
        "Maximum file size",
        "Data segment size",
        "Stack size",
        "Core file size",
        "Resident set size",
        "Number of processes",
        "Number of open files",
        "Locked memory",
        "Address space"
    };

    int n = sizeof(resources) / sizeof(resources[0]);

    printf("SYSTEM RESOURCE LIMITS\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        if (getrlimit(resources[i], &limit) == -1)
        {
            perror(names[i]);
            continue;
        }

        printf("\nResource: %s\n", names[i]);

        if (limit.rlim_cur == RLIM_INFINITY)
            printf("Soft limit: Unlimited\n");
        else
            printf("Soft limit: %llu\n",
                   (unsigned long long)limit.rlim_cur);

        if (limit.rlim_max == RLIM_INFINITY)
            printf("Hard limit: Unlimited\n");
        else
            printf("Hard limit: %llu\n",
                   (unsigned long long)limit.rlim_max);
    }

    return 0;
}


/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/2$ ./2
SYSTEM RESOURCE LIMITS
--------------------------------------------------

Resource: CPU time
Soft limit: Unlimited
Hard limit: Unlimited

Resource: Maximum file size
Soft limit: Unlimited
Hard limit: Unlimited

Resource: Data segment size
Soft limit: Unlimited
Hard limit: Unlimited

Resource: Stack size
Soft limit: 8388608
Hard limit: Unlimited

Resource: Core file size
Soft limit: 0
Hard limit: Unlimited

Resource: Resident set size
Soft limit: Unlimited
Hard limit: Unlimited

Resource: Number of processes
Soft limit: 46043
Hard limit: 46043

Resource: Number of open files
Soft limit: 10240
Hard limit: 1048576

Resource: Locked memory
Soft limit: 67108864
Hard limit: 67108864

Resource: Address space
Soft limit: Unlimited
Hard limit: Unlimited

*/
