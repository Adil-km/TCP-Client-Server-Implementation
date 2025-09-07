#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 8080

int main() {
    int server_socket, client_socket;
    struct sockaddr_in address;
    char buffer[1024] = {0};
    const char *response = "Welcome! You are connected to TCP server.";
    socklen_t addrlen = sizeof(address);

   
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("[-]Socket error");
        exit(1);
    }
    printf("[+]TCP server socket created\n");

  
    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("[-]setsockopt failed");
        exit(1);
    }


    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("[-]Binding error");
        exit(1);
    }
    printf("[+]Bind to the port %d\n", PORT);

 
    if (listen(server_socket, 5) < 0) {
        perror("[-]Listen failed");
        exit(1);
    }
    printf("[+]TCP server is listening...\n");

    while (1) {
        printf("[+]Waiting for client...\n");
        client_socket = accept(server_socket, (struct sockaddr*)&address, &addrlen);
        if (client_socket < 0) {
            perror("[-]Accept failed");
            continue;
        }
	printf("[+]client is connected!\n");
        send(client_socket, response, strlen(response), 0);
        printf("[+]Greeting sent to client\n\n");

        memset(buffer, 0, sizeof(buffer));
        int valread = read(client_socket, buffer, sizeof(buffer) - 1);
        if (valread > 0) {
            buffer[valread] = '\0';
	    printf("[+]A message received from client\n");
            printf("[+](client): %s\n", buffer);
        }

        close(client_socket);
        printf("[+]Client disconnected\n\n");
    }

    close(server_socket);
    printf("[+]Server shut down\n");
    return 0;
}

