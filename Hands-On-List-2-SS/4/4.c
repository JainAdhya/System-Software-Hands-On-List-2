
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

/* Read the timestamp counter before execution */
static inline uint64_t read_tsc_start()
{
    uint32_t low, high;

    __asm__ volatile (
        "lfence\n\t"
        "rdtsc"
        : "=a" (low), "=d" (high)
        :
        : "memory"
    );

    return ((uint64_t)high << 32) | low;
}

/* Read the timestamp counter after execution */
static inline uint64_t read_tsc_end()
{
    uint32_t low, high, aux;

    __asm__ volatile (
        "rdtscp\n\t"
        "lfence"
        : "=a" (low), "=d" (high), "=c" (aux)
        :
        : "memory"
    );

    return ((uint64_t)high << 32) | low;
}

int main()
{
    uint64_t start, end, elapsed;
    pid_t ppid;

    /* Read TSC before the system calls */
    start = read_tsc_start();

    /* Execute getppid() 100 times */
    for (int i = 0; i < 100; i++)
    {
        ppid = getppid();
    }

    /* Read TSC after the system calls */
    end = read_tsc_end();

    elapsed = end - start;

    printf("Parent process ID: %d\n", (int)ppid);
    printf("Number of getppid() calls: 100\n");
    printf("Total TSC ticks: %llu\n",
           (unsigned long long)elapsed);
    printf("Average TSC ticks per call: %.2f\n",
           elapsed / 100.0);

    return 0;
}


/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/4$ ./4
Parent process ID: 491
Number of getppid() calls: 100
Total TSC ticks: 149378
Average TSC ticks per call: 1493.78

*/
