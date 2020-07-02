#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

int main(){
	
	int n = 1000000;
	int pid = fork();
	
	for(int i = 0; i < n; i++){
				
		if(pid == 0){
			printf("hello from child\n");	
		} else {
			printf("hello from parent\n");
		}
	}
}
