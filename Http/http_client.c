#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

// contains fn to convert network addresses => ip add to format that structures understand
#include <arpa/inet.h>

int main(int argc, char *argv[]){
	
	// storing address of server from cmd line
	char *address;
	address = argv[1];
	
	printf("address : %s", address);

	// create a socket
	int client_socket;
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	// connect to an address
	struct sockaddr_in remote_address;
	remote_address.sin_family = AF_INET;
	remote_address.sin_port = htons(80);
	
	// previously we were doing INADDR_ANY but we are specific now
	// string add => format for our add structure
	inet_aton(address, &remote_address.sin_addr);
	//      address , where to store the converted add
	
	
	connect(client_socket, (struct sockaddr *) &remote_address, sizeof(remote_address));
	
	char request[] = "GET / HTTP/1.1\r\n\n";
	char response[4096];
	
	send(client_socket, request, sizeof(request), 0);
	
	recv(client_socket, &response, sizeof(response), 0);
	
	printf("Response from the server : %s\n" , response);
	close(client_socket);
	

}


