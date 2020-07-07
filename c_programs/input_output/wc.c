#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <err.h>
#include <ctype.h>

int main(int argc, char* argv[]){

	if(argc != 2){
		exit(-1);	
	}
	
	int lines = 0;
	int chars = 0;
	int words = 0;
		
	int fd1 = open(argv[1], O_RDONLY);

	if(fd1 == -1){
		err(1, "%s", argv[1]);
	}
	
	char c;
	int word = 0;
	
	while(read(fd1, &c, 1) > 0){		
		if(c == '\n'){
			lines++;
		}
		
		chars++;			
		
		if(word && isspace(c)){
			word = 0;
		}
		
		if(!word && !isspace(c)){
			word = 1;
			words++;
		} 
	}
	
	printf("%d %d %d %s\n", lines, words, chars, argv[1]);
	exit(0);
}
