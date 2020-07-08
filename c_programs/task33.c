#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdint.h>
#include<string.h>
#include<err.h>

int main(int argc, char** argv){
	/*dont forget to open for reading and writing
	*/
	if(argc != 2){
		errx(1, "need exactly one argument");
	}
	int fd = open(argv[1], O_RDWR);
	
	if(fd == -1){
		err(2, "%s", argv[1]);
	}
	
	uint64_t count[256];
	
	for(int i = 0; i < 256; i++){
		count[i] = 0;
	}
	
	uint8_t b;
	
	while(read(fd, &b, 1) > 0){
		count[b]++;
	}
	
	lseek(fd, 0, SEEK_SET);
	
	for(int i = 0; i < 256; i++){
		uint8_t num = (uint8_t)i;
		while(count[i]-- > 0)
			write(fd, &num, 1);
	}
	
	close(fd);
	exit(0);
}
