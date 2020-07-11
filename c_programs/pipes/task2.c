#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<err.h>

int main(int argc, char** argv){
	
	if(argc != 2){
		errx(1, "usage %s <string>\n", argv[0]);
	}
	
	int pipefd[2];
	pid_t cpid;
	char buf;
	
	if(pipe(pipefd) == -1){
		err(2, "pipe");
	}
		
	cpid = fork();
	
	if(cpid == -1){
		err(3, "fork");
	}
	
	if(cpid > 0){
		//parent		
		close(pipefd[0]); //close unused read end
		write(pipefd[1], argv[1], strlen(argv[1]));
		close(pipefd[1]); // close write end
		wait(NULL);
		exit(0);
	}else if(cpid == 0){
		//child
		close(pipefd[1]);// close unused end
		while(read(pipefd[0], &buf, 1) > 0){
			write(1, &buf, 1);
		}
		close(pipefd[0]); // close read end
		exit(0);
	}	
}
