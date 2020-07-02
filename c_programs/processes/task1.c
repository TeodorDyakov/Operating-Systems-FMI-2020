#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<err.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char** argv){
		
	if(argc < 2){
		err(99, "no command specified!\n");
		return 0;
	}
	
	char path[255];

	strcpy(path, "/bin/");
	strcat(path, argv[1]);
		
	pid_t pid = fork();
	
	if(pid > 0){
		wait(NULL);
		printf("%s\n", path);
	} else {
		execlp(path, argv[1], (char*)NULL);
	}
	
	exit(0);
	
}
