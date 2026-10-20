#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int pipe1[2], pipe2[2];
    pid_t pid;

    char parent_msg[] = "Hello Child, how are you?";
    char child_msg[]  = "Hi Parent, I am good!";
    char buffer[100];

    if(pipe(pipe1) == -1){
        perror("pipe1");
        exit(1);
    }

    if(pipe(pipe2) == -1){
        perror("pipe2");
        exit(1);
    }

    pid = fork();

    if(pid < 0){
        perror("fork");
        exit(1);
    }

    if(pid > 0){
        // ---------------- Parent Process ----------------
        close(pipe1[0]); // Close read end of pipe1 - no more reading by parent
        close(pipe2[1]); // Close write end of pipe2 - no more write from child

        printf("Parent sending msg: %s\n", parent_msg);
        write(pipe1[1], parent_msg, strlen(parent_msg)+1);

        read(pipe2[0], buffer, sizeof(buffer));
        printf("Parent received msg: %s\n", buffer);

        close(pipe1[1]);
        close(pipe2[0]);
    }
    else{
        // ---------------- Child Process ----------------
        close(pipe1[1]); // Close write end of pipe1 - no more writing from Parent
        close(pipe2[0]); // Close read end of pipe2 - this time child writes

        read(pipe1[0], buffer, sizeof(buffer));
        printf("Child received msg: %s\n", buffer);

        printf("Child sending msg: %s\n", child_msg);
        write(pipe2[1], child_msg, strlen(child_msg)+1);

        close(pipe1[0]);
        close(pipe2[1]);
    }

    return 0;
}


/* Output:

adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/16$ ./16
Parent sending msg: Hello Child, how are you?
Child received msg: Hello Child, how are you?
Child sending msg: Hi Parent, I am good!
Parent received msg: Hi Parent, I am good!

*/
