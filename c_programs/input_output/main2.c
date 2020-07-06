#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
 
int main(int argc, char* argv[]){
	char c;
	if(argc > 1){
		int fd1 = open(argv[1], O_RDONLY);
		int count = 0;		
		while((read(fd1, &c, 1) > 0) && (count < 10)){
			if(c == '\n'){
				count++;			
			}
			write(STDOUT_FILENO, &c, 1);
		}
	}
}
