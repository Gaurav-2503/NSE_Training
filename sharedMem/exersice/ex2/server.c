/*
	Write a program that create a shared memory sengment and waits until two other seperate processes writes something into that shared memory segment after which it prints what is written in that shared memory.
	
	for the communication to take place assume that the process 1 (Server) writes 1 in the 1st postion of the shared memory and waits : 
		
	Process 2 (Client1) writes 2 in the first position of shared memory and goes on to write something and then process 3 (Client2) writes 3 in the first position of shared memory and goes on to write memory and finally the process 1 (Server) prints what is in the shared memory written by two processes.

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/shm.h>
#include <unistd.h>


int main(){

	int shmid;
	char *buff, *s;
	
	// creating thr shared memory space and getting its unique id
	shmid = shmget((key_t)2005, sizeof(char)*1024, 0666 | IPC_CREAT);
	
	// attaching the process	
	buff = shmat(shmid, NULL, 0);

	
	// writting to the shared memory
	s = "Hello from Kernel, I am Server. Save Earth. Save Food.";
	
	// copying the content of dummy string s to the shared memory buffer
	strncpy(buff+1, s, sizeof(char)*1023);    // not 1024 = excluding control bit, 0th index
	
	
	//printf("\nThe Server has written : %s\n", s);  // this is wrong
		/* Reason : 
			- s is a pointer which is read-only. so when you assign string to it. that doesn't change the shared memory 
			- s just points to a read-only section of memory where the literal resides. This does not affect the shared memory region
			- s as a pointer does not alter the contents of the memory buff points to.	
		*/
	
	// Correct way
	printf("\nThe Server has written : %s\n", buff+1);

	// marking the flag
	*buff = 0;
	
	while(1){
		if(*buff == 1) {
			printf("\nThe 1st client has written : %s\n", buff+1);	
			*buff = 0;
		}
		else if(*buff == 2){
			printf("\nThe 2nd client has written : %s\n", buff+1);
			break;
		}
		sleep(1);
	}
	
	// Detaching the memory
	shmdt(buff);
	
	// Deleting the shared memory
	shmctl(shmid, (key_t)2005, NULL);
	
	
	
	
}
