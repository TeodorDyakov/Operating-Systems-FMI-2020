#include<unistd.h>
#include<fcntl.h>
#include<wait.h>
#include<err.h>
/*
This program takes 2 arguments - the name of two commands
it redirects the stdout of the first command to the file tmp
and executes the first command
Then it redirects the stdin of the second command to tmp
and executes the second command.
*/

int main(int argc, char** argv){
	
	int fd = open("tmp", O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	int cpid = fork();
	
	if(cpid == -1){
		err(1, "fork");
	}
	
	if(cpid == 0){	
		dup2(fd, 1);
		execlp(argv[1], "", NULL);			
	}
	
	wait(NULL);	
	lseek(fd, 0, SEEK_SET);
	dup2(fd, 0);
	
	execlp(argv[2], "", NULL);	
}
