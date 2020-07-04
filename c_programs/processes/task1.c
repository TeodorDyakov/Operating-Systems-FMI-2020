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
		
	if(argc < 2){
		err(99, "no command specified!\n");
		return 0;
	}
	
	char path[path_len + 1];
	path[path_len] = '\0';
	
	strcpy(path, "/bin/");
	strncat(path, argv[1], path_len - strlen(path));
		
	pid_t pid = fork();
	
	if(pid < 0){
		err(1, "Error in forking process!");
	} else if(pid > 0){
		wait(NULL);
		printf("Path of executed command: %s\n", path);
	} else {
		execlp(path, argv[1], (char*)NULL);
	}
	
	exit(0);
	
}
