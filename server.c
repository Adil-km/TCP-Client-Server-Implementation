#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 8080

int main(){

	int server_socket, client_socket;
	struct sockaddr_in address;
	char buffer[1024] = {0};
	const char *response = "This is from TCP server!!!!";
	socklen_t addrlen = sizeof(address);

	server_socket = socket(AF_INET,SOCK_STREAM,0);
	if(server_socket < 0){
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

	int n = bind(server_socket, (struct sockaddr*)&address, sizeof(address));
	if(n < 0){
		perror("[-]Binding error");
		exit(1);
	}
	printf("[+]Bind to the port %d\n",PORT);


	if (listen(server_socket, 5) < 0) {
        	perror("[-]Listen failed");
        	exit(1);
    	}
    	printf("[+]TCP server is listening...\n");

	while(1){

		printf("waiting for client..\n");
		client_socket = accept(server_socket, (struct sockaddr*)&address, &addrlen);
		if(client_socket<0){
			printf("[-]Accept failed....\n");
			continue;
		}
		memset(buffer, 0, 1024);
		int valread = read(client_socket, buffer, 1024);
		if(valread > 0){
			printf("From client: %s\n",buffer);
		}

		send(client_socket, response, strlen(response),0);
		printf("[+]Response sent to client\n");

		close(client_socket);
		printf("[+]client disconnected\n");
	}


	close(server_socket);
	printf("[+]Connection disconnected......\n");

	return 0;
}
