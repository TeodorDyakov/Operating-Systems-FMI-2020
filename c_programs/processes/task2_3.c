#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<err.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char** argv){
	
	pid_t pid = 1;
	
	for(int i = 1; i < argc; i++){		
		if(pid > 0){
			pid = fork();			
		}else if(pid == 0){
			char buf[200];
			buf[sizeof(buf) - 1] = '\0';
			strcpy(buf, "/bin/");
			strcat(buf, argv[i]);
			execlp(buf, argv[i], NULL);
		} else {
			perror();
			errx(1, "error in fork()");
		}
	}
		
	if(pid > 0){
		for(int i = 1; i < argc; i++){
			int status;
			int cpid = wait(&status);
			if(cpid == -1){
				perror("waitpid");
				exit(EXIT_FAILURE);
			}
			if(WIFEXITED(status)){
				printf("pid: %d exited with status: %d\n", cpid, WEXITSTATUS(status));
			} else{
				err(1, "child did not terminate normally");
			}	
		}
	}	
	
	exit(0);
	
}
