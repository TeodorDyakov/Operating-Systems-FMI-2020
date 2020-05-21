#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char* argv[]){
	char c;
	if(argc > 2){
		int type = 0;
		if(strcmp(argv[1], "-w") == 0){
			type = 1;
		}
		if(strcmp(argv[1], "-c") == 0){
			type = 2;
		}
		if(strcmp(argv[1], "-l") == 0){
			type = 3;
		}
		int fd1 = open(argv[2], O_RDONLY);
		int count = 0;		
		while(read(fd1, &c, 1)){
			if((type == 1) && (c == '\n' || c == ' ')){
				count++;			
			}
			if(type == 2){
				count++;			
			}
			if(type == 3 && c == '\n'){
				count++;			
			}
		}
		printf("%d %s\n", count, argv[2]);
	}
}
