#include<unistd.h>
#include<stdio.h>
#include<err.h>
#include<stdlib.h>

int main(){

	if((execlp("/bin/ls", "ls", "-l", NULL)) == -1){
		err(99, "error in executing ls -l");
	} else {		
		printf("%s", "hello");
	}
	exit(0);
}
