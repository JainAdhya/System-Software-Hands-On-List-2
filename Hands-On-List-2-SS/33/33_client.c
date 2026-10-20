#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket");
        exit(1);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);

    if (inet_pton(AF_INET, "172.21.137.43",
                  &server_addr.sin_addr) != 1) {
        printf("Invalid server IP address.\n");
        close(sock);
        return 1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr,
                sizeof(server_addr)) == -1) {
        perror("connect");
        close(sock);
        exit(1);
    }

    // Send message to server
    char message[] = "Hello from client!";
    send(sock, message, strlen(message), 0);

    // Receive server reply
    int n = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (n > 0) {
        buffer[n] = '\0';
        printf("Message from server: %s\n", buffer);
    }

    close(sock);

    return 0;
}

/* Output:

SERVER:
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/33$ hostna>
172.21.137.43
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/33$ nano 3>
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/33$ nano 3>
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/33$ gcc 33>
gcc 33_client.c -o client
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/33$ ./serv>
Server waiting for client on port 8080...
Client connected.
Message from client: Hello from client!

CLIENT:
adhya@adhya:~/System-Software-Hands-On-List-2/Hands-On-List-1-SS/33$ ./clie>
Message from server: Hello from server!

*/
