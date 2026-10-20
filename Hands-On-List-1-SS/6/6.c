
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg)
{
    int thread_num = *(int *)arg;

    printf("Thread %d is running.\n", thread_num);

    return NULL;
}

int main()
{
    pthread_t threads[3];
    int thread_num[3];

    /* Create three threads */
    for (int i = 0; i < 3; i++)
    {
        thread_num[i] = i + 1;

        if (pthread_create(&threads[i], NULL,
                           thread_function, &thread_num[i]) != 0)
        {
            perror("pthread_create");
            return 1;
        }
    }

    /* Wait for all three threads to finish */
    for (int i = 0; i < 3; i++)
    {
        if (pthread_join(threads[i], NULL) != 0)
        {
            fprintf(stderr, "pthread_join failed\n");
            return 1;
        }
    }

    printf("All threads have completed.\n");

    return 0;
}


/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/6$ ./6
Thread 1 is running.
Thread 2 is running.
Thread 3 is running.
All threads have completed.

*/
