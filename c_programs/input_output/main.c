#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
 
int main() 
{   
	char c;
	int fd1, fd2;
	fd1 = open("foo.txt", O_RDONLY);
	if(fd1 == -1){
		write(2, "error", 5);
		exit(-1);
	}
	fd2 = open("bar.txt", O_WRONLY);
	if(fd2 == -1){
		write(2, "error", 5);
		close(fd1);
		exit(-1);
	}
	while(read(fd1, &c, 1)){
		write(fd2, &c, 1);	
	}
	exit(0);	
} 	
