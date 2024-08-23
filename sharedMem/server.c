#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/shm.h>
#include <string.h>


int main()  {
	
	int i;
	void *shared_memory;      // memory where the shared memory is attached to the process space
				 // pointer to the shared memory space
	char buff[100];             // buffer to write and read from
	int shmid;           // unique segment identifier for the shared memory
	
	// creating a shared memory section
	shmid = shmget((key_t)2003, 2048, 0666 | IPC_CREAT);  
		   /* ( unique key = 2003 , (key_t) = data type use for keys in system V IPC,
		             shared memory segment size in bytes,
		                 permissions(0666=rw) | flag to create the memory segment if not created alreay)
		   */   
	
	printf("The key of shared memory is : %d\n", shmid);
	
	// attaching the process to the shared memory
	//returns a pointer to the shared memory segment
	shared_memory = shmat(shmid, NULL, 0);
		/*   (  unique key , 
			    attaching address - if NULL then system automatically assigns address,
			    	flag for accesss type and other attaching ways )
		*/  
	
	printf("Process attached at address : %p\n", shared_memory);
	
	printf("Enter some daya to write to the shared memory : ");
	fflush(stdout);
	int len = read(0, buff, 100);	 // get input from user 
	 /* ( 0 = standard input (terminal, console) , 
	 	buffer to read or write, 
	 		size of bytes to read or write )
	 */
	
	 	if(len > 0 && buff[len-1] == '\n'){
	 		buff[len-1] = '\0';
	 	} else {
	 		buff[len-1] = '\0';
	 	}
	 
	 printf("\nThe size of buffer is : %d\n", len);
	
	strcpy(shared_memory, buff);   // data written to shared memory			
	
	printf("\nYou wrote : %s\n" , (char*)shared_memory);	
	
	
/* Now to avoid garbage characters after our input, as buffer size is big and we are inputting small values. so it cn happen that last character is not \0. we can avoid it by followwing ways. 			
	- Ensure proper Null termination
*/
	 /* 
	 	int len = read(0, buff, 100);
	 	if(len > 0 && buff[len-1] == '\n'){
	 		buff[len-1] = '\0';
	 	} else {
	 		buff[len-1] = '\0';
	 	}
	 */	
	
	
	
	
	
	
	
	
	
	
	
	
	
}



















