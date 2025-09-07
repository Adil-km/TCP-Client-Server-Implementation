#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock;
    struct sockaddr_in server_address;
    char buffer[1024];
    char message[256];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("[-]Socket error");
        exit(1);
    }
    printf("[+]TCP client socket created\n");

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

    if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("[-]Connection failed");
        exit(1);
    }
    printf("[+]Connected to the TCP server\n\n");


    memset(buffer, 0, sizeof(buffer));
    int valread = read(sock, buffer, sizeof(buffer)-1);
    if (valread > 0) {
        buffer[valread] = '\0';
        printf("[+](server): %s\n", buffer);
    }

    printf("Enter your message: ");
    if (fgets(message, sizeof(message), stdin) == NULL) {
        perror("[-]Input error");
        close(sock);
        exit(1);
    }
    message[strcspn(message, "\n")] = '\0';

    send(sock, message, strlen(message), 0);

    close(sock);
    printf("[+]Connection closed\n");
    return 0;
}

