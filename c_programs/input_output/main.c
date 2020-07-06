#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
 
int main() 
{   
	int fd1 = open("foo.txt", O_RDONLY);
	
	if(fd1 == -1){
		write(2, "error", 5);
		exit(-1);
	}
	
	int fd2 = open("bar.txt", O_WRONLY);
	
	if(fd2 == -1){
		write(2, "error", 5);
		close(fd1);
		exit(-1);
	}
	
	int read_cnt = 0;
	char c;
	
	while((read_cnt = read(fd1, &c, 1)) > 0){
		if(read_cnt != write(fd2, &c, 1)){
			const char* err_msg = "error in writing";
			write(2, err_msg, strlen(err_msg));			
			exit(-1);
		}	
	}
	
	exit(0);	
} 	
