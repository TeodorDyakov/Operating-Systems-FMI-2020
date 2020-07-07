#include<stdio.h> 
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int is_little_endian(){
	unsigned int i = 1;  
    char *c = (char*)&i;  
    if (*c)  
    	return 1;
	
	return 0;
}

int main(int argc, char** argv){
	if(argc != 2){
		errx(1, "err");	
	}
			
	int fd = open(argv[1], O_RDONLY);  
	if(fd == -1){
		err(2, "%s", argv[1]);
	}
	
	int min = 0;
	int max = 0;
	
	int read_cnt = 0;
	char buf[2];
		
	while((read_cnt = read(fd, &buf, sizeof(buf))) > 0){
		if(read_cnt == 1){
			//this means we have reached EOF so we stop reading
			break;
		}
		u_int16_t a = 0;
		if(is_little_endian()){
			//swap byte order if on little endian arch
			char swapped[2] = {buf[1], buf[0]};
			/*
			cast the address of swapped to a pointer
			to unsigned 16 bit int then dereference it 
			*/
			a = *(u_int16_t*)(&swapped);		
		}else{
			a = *(u_int16_t*)(&buf);
		}						
		printf("%d\n", a); 				
	}
	
	close(fd);
	exit(0);  
}  
 
