#include<unistd.h>
#include<fcntl.h>
#include<wait.h>

/*
This program takes 2 arguments - the name of two commands
it redirects the stdout of the first command to the file tmp
and executes the first command
Then it redirects the stdin of the second command to tmp
and executes the second command.
*/

int main(int argc, char** argv){
	
	int fd = open("tmp", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	int cpid = fork();
	
	if(cpid == 0){	
		dup2(fd, 1);
		execlp(argv[1], "ls", NULL);			
	}
	
	wait(NULL);
	close(fd);
	
	fd = open("tmp", O_RDWR, S_IRUSR | S_IWUSR);
	dup2(fd, 0);
	
	cpid = fork();
	
	if(cpid == 0){
		execlp(argv[2], "wc", NULL);
	}
	
	wait(NULL);
	close(fd);
}
