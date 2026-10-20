#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>

int main(){
    int choice;
    printf("Choose:\n");
    printf("1. Ignore SIGINT (Ctrl+C)\n");
    printf("2. Reset SIGINT to default\n");
    scanf("%d", &choice);

    if(choice == 1){
        printf("Ignoring SIGINT for 10 seconds...\n");
        signal(SIGINT, SIG_IGN);
        sleep(10);
        printf("Done. Program will exit normally.\n");
    } 
    else if(choice == 2){
        printf("Setting SIGINT to default action...\n");
        signal(SIGINT, SIG_DFL);
        while(true) 
            sleep(1); // Ctrl+C to terminate the program
    } 
    else
        printf("Invalid choice!\n");

    return 0;
}


/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/9$ ./9
Choose:
1. Ignore SIGINT (Ctrl+C)
2. Reset SIGINT to default
1
Ignoring SIGINT for 10 seconds...
^C
^C
^C
^C
Done. Program will exit normally.
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/9$
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/9$ ./9
Choose:
1. Ignore SIGINT (Ctrl+C)
2. Reset SIGINT to default
2
Setting SIGINT to default action...
^C

*/
