// TCP Server

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>



// structure to store the address info
#include <netinet/in.h>


int main(){
	
	char server_message[256] = "Hii!, I am a server. Bye...";
	
	// create a socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
			      // internet(ipv4), TCP(reliable), protocol(0) 
	
	// Define the address structure
	struct sockaddr_in server_address;  
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
			// data format is diff , use conversion function(htons())
			// don't use well known port
	server_address.sin_addr.s_addr = INADDR_ANY;
				       // 0.0.0.0
				       
	
	// Bind the socket to ip and port
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	
	
	// Start listening to connections
	listen(server_socket , 5);
		// sockfd  , backlog = how many connections to allow in waiting queue
		// Defines the maximum length to which the queue of pending connections for sockfd may grow
	
	// integer to hold the client socket fd
	int client_socket;
	
	// Accept the connection
	client_socket = accept(server_socket, NULL, NULL);
			// socket on which we are accepting the connections
			// Address of the client/peer socket
			// addlen - size of the structure pointed by addr
	
	
	// send the message to client
	send(client_socket, &server_message, sizeof(server_message), 0);
	
	//  close the socket
	close(server_socket);
			
	
	return 0;
}



























