#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<err.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>

int main(int argc, char** argv){
	pid_t pid = fork();
	
	if(pid < 0){
		errx(1, "error in fork()");
	}
	
	int fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC);	
	if(fd == -1){
		err(2, "%s", argv[1]);
	}

	if(pid == 0){
		const char* msg = "foobar";
		write(fd, msg, strlen(msg));
		close(fd);
	} else{
		wait(NULL);
		
		char buf[2];
		fd = open(argv[1], O_RDONLY);
		
		while(read(fd, &buf, sizeof(buf)) > 0){
			write(1, &buf, sizeof(buf));
			write(1, " ", 1);
		}
		close(fd);	
	}
	exit(0);
}
