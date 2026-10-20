
#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

/* Function to print a system configuration value */
void print_limit(const char *name, int option)
{
    long value;

    errno = 0;
    value = sysconf(option);

    printf("%s: ", name);

    if (value == -1)
    {
        if (errno != 0)
            perror("sysconf");
        else
            printf("Value is indeterminate or unavailable\n");
    }
    else
    {
        printf("%ld\n", value);
    }
}

int main()
{
    long page_size;
    long total_pages;
    long available_pages;

    printf("SYSTEM LIMITATIONS\n");
    printf("----------------------------------------\n");

    /* a. Maximum length of arguments to exec family */
    print_limit("a. Maximum argument length for exec",
                _SC_ARG_MAX);

    /* b. Maximum simultaneous processes per user ID */
    print_limit("b. Maximum processes per user ID",
                _SC_CHILD_MAX);

    /* c. Number of clock ticks per second */
    print_limit("c. Clock ticks per second",
                _SC_CLK_TCK);

    /* d. Maximum number of open files */
    print_limit("d. Maximum open files",
                _SC_OPEN_MAX);

    /* e. Size of a memory page */
    errno = 0;
    page_size = sysconf(_SC_PAGESIZE);

    if (page_size == -1)
    {
        perror("sysconf(_SC_PAGESIZE)");
        return 1;
    }

    printf("e. Page size: %ld bytes\n", page_size);

    /* f. Total number of physical memory pages */
    errno = 0;
    total_pages = sysconf(_SC_PHYS_PAGES);

    if (total_pages == -1)
    {
        if (errno != 0)
            perror("sysconf(_SC_PHYS_PAGES)");
        else
            printf("f. Total physical pages: Unavailable\n");
    }
    else
    {
        printf("f. Total physical pages: %ld\n", total_pages);
    }

    /* g. Number of currently available physical memory pages */
    errno = 0;
    available_pages = sysconf(_SC_AVPHYS_PAGES);

    if (available_pages == -1)
    {
        if (errno != 0)
            perror("sysconf(_SC_AVPHYS_PAGES)");
        else
            printf("g. Available physical pages: Unavailable\n");
    }
    else
    {
        printf("g. Available physical pages: %ld\n",
               available_pages);
    }

    return 0;
}

/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/5$ ./5
SYSTEM LIMITATIONS
----------------------------------------
a. Maximum argument length for exec: 2097152
b. Maximum processes per user ID: 46043
c. Clock ticks per second: 100
d. Maximum open files: 10240
e. Page size: 4096 bytes
f. Total physical pages: 2949544
g. Available physical pages: 2635299

*/
