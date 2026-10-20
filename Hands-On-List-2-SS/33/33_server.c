#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[1024];

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(1);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to port
    if (bind(server_fd, (struct sockaddr *)&server_addr,
             sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_fd);
        exit(1);
    }

    // Listen for connections
    if (listen(server_fd, 5) == -1) {
        perror("listen");
        close(server_fd);
        exit(1);
    }

    printf("Server waiting for client on port 8080...\n");

    // Accept client connection
    client_fd = accept(server_fd,
                       (struct sockaddr *)&client_addr,
                       &client_len);

    if (client_fd == -1) {
        perror("accept");
        close(server_fd);
        exit(1);
    }

    printf("Client connected.\n");

    // Receive message from client
    int n = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (n > 0) {
        buffer[n] = '\0';
        printf("Message from client: %s\n", buffer);
    }

    // Send reply
    char reply[] = "Hello from server!";
    send(client_fd, reply, strlen(reply), 0);

    close(client_fd);
    close(server_fd);

    return 0;
}

/* Output:

SERVER:
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/33$ hostname -I
172.21.137.43
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/33$ nano 33_server.c
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/33$ nano 33_client.c
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/33$ gcc 33_server.c -o server
gcc 33_client.c -o client
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/33$ ./server
Server waiting for client on port 8080...
Client connected.
Message from client: Hello from client!

CLIENT:
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/33$ ./client
Message from server: Hello from server!

*/
