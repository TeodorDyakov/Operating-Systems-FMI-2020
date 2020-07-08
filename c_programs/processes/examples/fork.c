#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

int main(){
	
	int n = 1000000;
	int pid = fork();
		
	if(pid == -1){
		exit(-1);
	}
	
	if(pid == 0){	
		for(int i = 0; i < n; i++){					
			printf("hello from child\n");
		}
	} else {
		for(int i = 0; i < n; i++){					
			printf("hello from parent\n");
		}
	}
	exit(0);
}
