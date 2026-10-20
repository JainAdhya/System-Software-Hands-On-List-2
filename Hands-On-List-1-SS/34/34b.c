#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BACKLOG 5
#define BUF_SIZE 1024

void *handle_client(void *arg){
    int client = *((int *)arg);
    free(arg);

    char buf[BUF_SIZE] = {0};
    int n = recv(client, buf, BUF_SIZE - 1, 0);
    if(n > 0){
        buf[n] = '\0';
        printf("Client: %s\n", buf);
        send(client, "Hello from server!\n", 19, 0);
    }
    close(client);
    pthread_exit(NULL);
}

int main(){
    int server = socket(AF_INET, SOCK_STREAM, 0);
    if(server < 0){ 
        perror("socket");   
        exit(1); 
    }

    int opt = 1;
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr = {AF_INET, htons(PORT), INADDR_ANY};
    bind(server, (struct sockaddr *)&addr, sizeof(addr));
    listen(server, BACKLOG);

    printf("Server listening on port %d...\n", PORT);

    while(1){
        struct sockaddr_in client_addr;
        socklen_t len = sizeof(client_addr);
        int client = accept(server, (struct sockaddr *)&client_addr, &len);
        if(client < 0){ 
            perror("accept"); 
            continue; 
        }

        printf("Connected: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        int *pclient = malloc(sizeof(int));
        *pclient = client;
        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, pclient);
        pthread_detach(tid);
    }

    close(server);
    return 0;
}




/* Output:

Server:
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/34$ ./server_thread
Server listening on port 8080...
Connected: 127.0.0.1:34420
Client: Hello How are u?

Connected: 127.0.0.1:37216
Client: Hello This is Client 2

Terminal Client 1:
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/34$ nc localhost 8080
Hello How are u?
Hello from server!

Terminal Client 2:
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/34$ nc localhost 8080
Hello How are u?
Hello from server!

*/
