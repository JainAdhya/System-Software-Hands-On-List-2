#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(){
    const char *fifo_name = "myfifo_sys";
    // mode: 0666 (read/write for all), S_IFIFO for FIFO
    if(mknod(fifo_name, S_IFIFO | 0666, 0) == -1){
        perror("mknod");
        exit(1);
    }
    printf("FIFO %s created successflly using mknod system call\n", fifo_name);
    return 0;
}

/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/19$ ./19d
FIFO myfifo_sys created successflly using mknod system call

*/
