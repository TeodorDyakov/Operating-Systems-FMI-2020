#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <wait.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>

#define PAGESIZE 4096

int v = 0;

int main(){
	uint8_t *shared_memory = mmap(NULL, PAGESIZE,
	 PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);	
	
	*shared_memory = 10;
	printf("%i\n", *shared_memory);

	int pid = fork();

	if(pid == 0){
		*shared_memory = 80;
	}else{
		wait(NULL);
		printf("%i\n", *shared_memory);
	}
}