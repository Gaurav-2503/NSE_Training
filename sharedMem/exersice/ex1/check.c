#include <stdio.h>
#include <stdlib.h>

#include <string.h>


int main() {
	
	char buff[26], *s;
	s = buff;
	for(int i=25; i>=0; i--){
		*s = (char)(65+i);
		s++;
	}
	s = buff;
	for(int i=0; i<=25; i++){
		printf("\nAt index %d : %c", i, *s);
		s++;
	}
	
	
	
}
