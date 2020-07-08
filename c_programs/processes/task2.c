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
	
	if(argc < 4){
		errx(1, "not enough arguments!\n");
	}
	
	for(int i = 1; i < 4; i++){
		
		char path[path_len + 1];
		path[path_len] = '\0';
		
		strcpy(path, "/bin/");
		strncat(path, argv[i], path_len - strlen(path));
			
		pid_t pid = fork();
		
		if(pid < 0){
			err(2, "Error in forking process!");
		} else if(pid > 0){
			
			int stat;
		
			pid_t cpid = wait(&stat);
			
			if(WIFEXITED(stat)){	
				printf("pid: %d Exit status: %d\n", cpid,
				WEXITSTATUS(stat));
			}else{
				printf("child did not exit normally\n");
			}
			
		} else{
			execlp(path, argv[i], (char*)NULL);
		}
	}
	
	exit(0);
	
}
