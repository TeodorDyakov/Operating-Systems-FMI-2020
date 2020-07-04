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
		err(1, "not enough arguments!\n");
		return 0;
	}
	
	for(int i = 1; i < 3; i++){
		
		char path[path_len + 1];
		path[path_len] = '\0';
		
		strcpy(path, "/bin/");
		strncat(path, argv[i], path_len - strlen(path));
			
		pid_t pid = fork();
		
		if(pid < 0){
			err(i + 1, "Error in forking process!");
		} else if(pid > 0){
			wait(NULL);
			printf("Path of executed command: %s\n", path);
		} else {
			execlp(path, argv[i], (char*)NULL);
		}
	}
	
	exit(0);
	
}
