#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
 
int main(int argc, char* argv[]){
	char c;
	if(argc > 1){
		int fd1 = open(argv[1], O_RDONLY);
		//printf("fd = %d", fd1);
		int count = 0;		
		while(read(fd1, &c, 1) && count < 10){
			if(c == '\n'){
				count++;			
			}
			write(0, &c, 1);
		}
	}
}
