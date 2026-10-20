#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(){
    const char *fifo_name = "myfifo_lib";
    if(mkfifo(fifo_name, 0666) == -1){
        perror("mkfifo");
        exit(1);
    }
    printf("FIFO %s created sccessfully using mkfifo library function\n", fifo_name);
    return 0;
}

/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/19$ ./19e
FIFO myfifo_lib created sccessfully using mkfifo library function

*/
