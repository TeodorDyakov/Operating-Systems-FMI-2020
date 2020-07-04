#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<string.h>

int main(int argc, char** argv){
	pid_t pid = fork();
	
	if(pid < 0){
		return 0;
	}
	
	int fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC);	

	if(pid == 0){
		write(fd, "foobar", strlen("foobar"));
		close(fd);
	} else{
		wait(NULL);
		
		char buf[2];
		fd = open(argv[1], O_RDONLY);
		
		while(read(fd, &buf, 2) > 0){
			write(1, &buf, 2);
			write(1, " ", 1);
		}
		close(fd);	
	}
}
