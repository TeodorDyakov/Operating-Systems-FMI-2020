#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<err.h>

int main(){
	
	int n = 100000;
	int pid = fork();

	if(pid != 0){ 
		pid_t child_id = wait(NULL);
		
		if(child_id == -1){
			err(1, "error in waiting");
		}
	}

	for(int i = 0; i < n; i++){			
		if(pid == 0){
			printf("hello from child\n");	
		} else {
			printf("hello from parent\n");
		}
	}
}
