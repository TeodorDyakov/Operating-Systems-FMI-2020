#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<err.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv){
	int fd = open("temp", O_CREAT | O_WRONLY, S_IRUSR, S_IWUSR);
	
	pid_t pid  = fork();
	
	if(pid == -1){
		exit(-1);
	}else if(pid > 0){
		wait(NULL);
		
		pid = fork();
		if(pid > 0){
			write(fd, "bar", 3);
		}
	}else{
		write(fd, "foo", 3);
	}
	close(fd);
}
