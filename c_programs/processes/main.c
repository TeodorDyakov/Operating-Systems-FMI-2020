#include<unistd.h>
#include<stdio.h>

int main(){

	if((execl("/bin/date", "date", NULL) == -1){
		err(99, "error execing file");
	} else {		
		printf("%s", "hello");
	}
}
