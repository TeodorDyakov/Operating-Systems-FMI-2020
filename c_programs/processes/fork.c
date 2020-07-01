#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

int main(){
	int pid = fork();
	
	if(pid == 0){
		printf("hello from child\n");	
	} else {
		printf("hello from parent\n");
	}
}
