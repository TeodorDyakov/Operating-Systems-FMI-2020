#include<unistd.h>
#include<fcntl.h>
#include<wait.h>
#include<err.h>
#include<string.h>

int main(int argc, char** argv){
	
	int pfd[2];
	
	if(pipe(pfd) == -1){
		errx(1, "pipe");
	}
	
	int cpid = fork();
	
	if(cpid == -1){
		err(1, "fork");
	}
	
	if(cpid == 0){	
		close(pfd[0]); //close unused read end
		write(pfd[1], argv[1], strlen(argv[1]));
		close(pfd[1]); 
		_exit(0);	
	}
	wait(NULL);		
	close(pfd[1]); //close unused write end
	dup2(pfd[0], 0); //redirect the stdin of parent to the read end of the pipe
	execlp("wc", "wc", "-c", NULL);	
}
