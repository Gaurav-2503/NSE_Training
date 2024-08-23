// TCP Client 

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

// structure to store the address info

#include <netinet/in.h>

int main() {
	
	// Create a socket
	int client_socket;
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	                	      // internet , stream(TCP), protocol(0=TCP)	
	   
	// Before we connect we need address to connect to
	// specifying an address for socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
			// data format is diff , use conversion function(htons())
			// don't use well known port
	server_address.sin_addr.s_addr = INADDR_ANY; 
					// 0.0.0.0	
					
	// Connect to socket
	int connection_status;
	connection_status = connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));	
	// connect returns an integer  0 = ok, -1 = not ok
	
	if(connection_status == -1){	
		printf("There was problem while connecting to the socket\n\n");
	}
	
	
	// to receive the data from server
	char server_response[256];
	recv(client_socket, &server_response, sizeof(server_response), 0);
										// flags
										
	// Print data that we get back
	printf("The response from server is %s\n" , server_response);	
	
	
	// close the socket
	close(client_socket);				
		

	return 0;

}
