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
	
	pid_t pid = fork();
	
	if(pid > 0){
		pid = fork();		
		if(pid > 0){
			pid = fork();
			if(pid > 0){
				int cpid = wait(NULL);
				printf("cpid: %d\n", cpid);	
				cpid = wait(NULL);
				printf("cpid: %d\n", cpid);
				cpid = wait(NULL);
				printf("cpid: %d\n", cpid);
			}
		}
	}
	
	
	exit(0);
	
}
