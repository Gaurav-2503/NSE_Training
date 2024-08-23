// Task 2
/*
	Parent should be server and child should be client
	
	Parent : 
		should crate shared memory and write capital english alphabets Z to A in it
	
	Child :
		should access that memory and read whatever is written by parent in it
*/

#include <stdio.h>
#include <stdlib.h>

#include <sys/shm.h>

#include <unistd.h>

#include <string.h>


int main() {

	int shmid;
	char *shm_ptr, *s;
	
	// creating shared memory 
	// we are using IPC_PRIVATE because child and parent process are involved in it
	shmid = shmget(IPC_PRIVATE, 27*sizeof(char), 0666 | IPC_CREAT);
	
	int child = fork();
	
	if(child == 0) {      // child process 
	
		// attach the memory
		shm_ptr = shmat(shmid, NULL, 0);
		
		// using the memory for our opration
		
		s = shm_ptr;
		s++;
		printf("\nIn child results are : \n");
		for(int i=1; i<=26; i++){
			printf("\nAt index %d : %c", i, *s);
			s++;
		}
		
		*shm_ptr = '-';
		
		// Detaching the shared memory
		shmdt(shm_ptr);
		
	}
	
	else {
			
		// attach the shared memory
		shm_ptr = shmat(shmid, NULL, 0);
	
		s = shm_ptr;
		s++;
		
		*shm_ptr = '*';
		
		for(int i=25; i>=0; i--){
			*s = (char)(65+i);
			s++;
		}
		
		s = shm_ptr;
		s++;
		
		/*for(int i=25; i>=0; i--){
			printf("\nAt index %d : %c", i, *s);
			s++;
		}*/
		
		// waiting until the client is doing his operation
		while(*shm_ptr == '*'){
			sleep(1);
		}
		
		// Detaching the shared memory
		shmdt(shm_ptr);
		
		// Deleting the shared memory
		shmctl(shmid, IPC_PRIVATE, NULL);
		
		
	}
	
	
	
	
	
	
	
	
	
	
	
}




























