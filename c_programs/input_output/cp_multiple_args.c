#include <stdio.h>
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char* argv[])
{
	int dir_fd = open(argv[argc - 1], __O_DIRECTORY);

	if(dir_fd == -1){
		err(1, "failed to open directory");	
	}

	for(int i = 1; i < argc - 1; i++){
		
		int fd = open(argv[i], O_RDONLY);
		if(fd == -1){
				err(99, "failed to open file");					
		}
		
		char c;

		char* path = strcat(argv[argc - 1], "/"); 
		path = strcat(path, argv[i]);

		int copy_fd = open(path, O_CREAT | O_WRONLY);
				
		if(copy_fd == -1){
				err(99, "failed to open file");					
		}

		while(read(fd, &c, 1)){
			write(dir_fd, &c, 1);		
		}
			
	}

	exit(0);
}
