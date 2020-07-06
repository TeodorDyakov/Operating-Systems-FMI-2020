#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<err.h>
#include<stdio.h>
#include<string.h>

#define path_len 255

int main(int argc, char** argv){
		
	if(argc < 3){
		errx(1, "not enough arguments!\n");
	}
	
	for(int i = 1; i < 3; i++){
		
		char path[path_len + 1];
		path[path_len] = '\0';
		
		strcpy(path, "/bin/");
		strncat(path, argv[i], path_len - strlen(path));
			
		pid_t pid = fork();
		
		if(pid < 0){
			err(2, "Error in forking process!");
		} else if(pid > 0){
			
			int stat;
		
			wait(&stat);
			
			if(WIFEXITED(stat)){ 
        		printf("Exit status: %d\n", WEXITSTATUS(stat)); 
			} else if(WIFSIGNALED(stat)){ 
	        	psignal(WTERMSIG(stat), "Exit signal");
			}
			
		} else{
			execlp(path, argv[i], (char*)NULL);
		}
	}
	
	exit(0);
	
}
