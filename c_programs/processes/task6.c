#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<err.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char** argv){
	
	pid_t pid;
	
	for(int i = 1; i < argc; i++){	
		pid = fork();		
		
		if(pid > 0){			
		}else if(pid == 0){
			char buf[200];
			buf[sizeof(buf) - 1] = '\0';
			strcpy(buf, "/bin/");
			strcat(buf, argv[i]);
			if(execlp(buf, argv[i], NULL) == -1){
				exit(EXIT_FAILURE);
			}else{
				exit(EXIT_SUCCESS);
			}
		} else {
			perror("fork");
			exit(EXIT_FAILURE);
		}
	}
	
	/*
	everything from here to end is in parent process
	*/
	
	int exited_success_cnt = 0;
	int exited_unsuccess_cnt = 0;
	
	for(int i = 1; i < argc; i++){
		
		int status;
		int cpid = wait(&status);
		
		if(cpid == -1){
			perror("wait");
			exit(-1);
		}
		if(WIFEXITED(status) && (WEXITSTATUS(status) == 0)){
			exited_success_cnt++;
		}else{
			exited_unsuccess_cnt++;
		}
	}	
	
	printf("number of commands that were\nsuccesful: %d\nunsuccesful: %d\n",
		exited_success_cnt, exited_unsuccess_cnt); 
	
	exit(0);
	
}
