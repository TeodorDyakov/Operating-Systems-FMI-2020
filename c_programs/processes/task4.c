#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<err.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>

int main(int argc, char** argv){
	int fd = open("temp", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if(fd == -1){
		err(1, "%s", "temp");
	}
	
	pid_t pid  = fork();
	
	if(pid == -1){
		close(fd);
		perror("fork");
		exit(-1);
	} else if(pid > 0){
		if (wait(NULL) == -1){
			close(fd);
			perror("wait");
			exit(-2);
		}
		
		pid = fork();

		if(pid == -1){
			close(fd);
			perror("fork");
			exit(-3);
		} else if(pid > 0){
			if(write(fd, "bar", 3) != 3){
				close(fd);
				errx(1, "error in writing to file");
			}
		}
	}else{
		if(write(fd, "foo", 3) != 3){
			close(fd);
			errx(1, "error in writing to file");
		}
	}
	
	close(fd);
	exit(0);
}
