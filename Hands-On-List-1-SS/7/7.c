
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg)
{
    printf("Thread ID: %lu\n",
           (unsigned long)pthread_self());

    return NULL;
}

int main()
{
    pthread_t threads[3];

    /* Create three threads */
    for (int i = 0; i < 3; i++)
    {
        if (pthread_create(&threads[i], NULL,
                           thread_function, NULL) != 0)
        {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }

    /* Wait for all threads to finish */
    for (int i = 0; i < 3; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}


/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/7$ ./7
Thread ID: 133736565831360
Thread ID: 133736557438656
Thread ID: 133736549045952

*/
