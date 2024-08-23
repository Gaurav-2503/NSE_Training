#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/shm.h>
#include <unistd.h>


int main(){

	int shmid;
	char *buff, *s;
	
	// Getting shared memory's unique id
	shmid = shmget((key_t)2005, sizeof(char)*1024, 0666 );
	
	// attaching the process	
	buff = shmat(shmid, NULL, 0);
	
	// writting to buffer 
	s = "Hello from OS, I am 2nd Client. Eat Healthy. Sleep well";
	
	// copying the content of dummy string s to the shared memory buffer
	strncpy(buff+1, s, sizeof(char)*1023);    // not 1024 = excluding control bit, 0th index
	
	// changing the flag
	*buff = 2;
	
	// Detaching the memory
	shmdt(buff);
	
	
}
