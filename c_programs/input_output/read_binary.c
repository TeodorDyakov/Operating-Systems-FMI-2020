#include<stdio.h> 
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<err.h>

int is_little_endian(){
	unsigned int i = 1;  
    char *c = (char*)&i;  
    if (*c)  
    	return 1;
	
	return 0;
}

int main(int argc, char** argv){
	if(argc != 3){
		errx(1, "err");	
	}
	
	int fd = open(argv[2], O_RDONLY);  
	
	if(fd == -1){
		err(2, "%s", argv[2]);
	}
		
	uint16_t min = INT16_MAX;
	uint16_t max = 0;
	
	int read_cnt = 0;
	char buf[2];
		
	while((read_cnt = read(fd, &buf, sizeof(buf))) > 0){
		if(read_cnt == 1){
			//this means we have reached EOF so we stop reading
			break;
		}
		uint16_t  a = 0;
		if(is_little_endian()){
			//swap byte order if on little endian arch
			char swapped[2] = {buf[1], buf[0]};
			/*
			cast the address of swapped to a pointer
			to unsigned 16 bit int then dereference it 
			*/
			a = *(uint16_t*)(&swapped);		
		} else {
			a = *(uint16_t *)(&buf);
		}
		
		if(strcmp(argv[1], "--min") == 0){
			if(min > a){
				min = a;
			}		 		
		} else if(strcmp(argv[1], "--max") == 0){
			if(max < a){
				max = a;
			}
		} else { 						
			printf("%d\n", a);
		} 				
	}
		
	if(strcmp(argv[1], "--min") == 0){
		printf("min is %d", min);		 		
	} else if(strcmp(argv[1], "--max") == 0){
		printf("max is %d", max);
	}

	close(fd);
	exit(0);  
}  
 
