#include<unistd.h>
#include<stdio.h>
#include<err.h>
#include<stdlib.h>

int main(){

	printf("hello");

	if(execlp("/bin/sleep", "sleep", "60", NULL) == -1){
		err(99, "Error in executing sleep"); 			
	}

	printf("goodbye");

}
