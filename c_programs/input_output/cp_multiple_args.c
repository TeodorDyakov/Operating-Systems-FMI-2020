#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char* argv[])
{
	char* dir_name = argv[argc - 1];
	int dir_fd = open(dir_name, __O_DIRECTORY);

	if(dir_fd == -1){
		close(dir_fd);
		err(1, "%s", dir_name);	
	}

	for(int i = 1; i < argc - 1; i++){
		
		int fd = open(argv[i], O_RDONLY);

		if(fd == -1){
				err(2, "%s", argv[i]);					
		}
			
		const size_t path_max_length = 255;
		
		char path[path_max_length + 1];
		path[path_max_length] = '\0';
	
		strncpy(path, dir_name, path_max_length);
		strncat(path, "/", path_max_length - strlen(path) - 1); 
		strncat(path, argv[i], path_max_length - strlen(path) - strlen(argv[i]));
	
		int copy_fd = open(path, O_CREAT | O_WRONLY);
				
		if(copy_fd == -1){
				err(3, "%s", path);					
		}
		
		char buf[4096];
		int read_cnt;
			
		while((read_cnt = read(fd, &buf, sizeof(buf))) > 0){
			if(read_cnt != write(copy_fd, &buf, read_cnt)){
				errx(4, "err");
			}		
		}
		close(fd);
		close(copy_fd);	
	}


	exit(0);
}
