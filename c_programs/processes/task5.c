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
			perror("fork");
		} else if(pid > 0){
			
			int stat;
		
			pid_t cpid = wait(&stat);
			if(pid == -1){
				perror("wait");
				exit(-1);
			}
			
			if(WIFEXITED(stat) && (WEXITSTATUS(stat) == 0)){	
				continue;
			}else{
				exit(-42);
			}			
		} else{
			if(execlp(path, argv[i], (char*)NULL) == -1){
				exit(-1);
			}
		}
	}
	
	exit(0);
	
}
