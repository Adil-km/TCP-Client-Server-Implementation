#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int main(){

	int sock;
	struct sockaddr_in server_address;
	char buffer[1024] = {0};
	const char *message = "Hi this is from client side";

	sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0){
		perror("[-]Socket error");
		exit(1);
	}
	printf("[+]TCP client socket created\n");

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	inet_pton(AF_INET,"127.0.0.1",&server_address.sin_addr);

	connect(sock, (struct sockaddr*)&server_address, sizeof(server_address));
	printf("[+]Connected to the server\n");

	send(sock, message, strlen(message),0);

	read(sock, buffer, 1024);
	printf("From client: %s\n",buffer);

	close(sock);

	return 0;
}
