#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdint.h>
#include<string.h>
#include<err.h>

int cmpfunc (const void * a, const void * b) {
   return ( *(uint32_t*)a - *(uint32_t*)b );
}

long filelength(const char*filpath) { // don't use that. Learn POSIX API
 	struct stat st;
   	if(stat(filpath, &st)) /*failure*/
	  	return -1; // when file does not exist or is not accessible
   	return (long) st.st_size;
}

void sort_file(char* name){
	int fd = open(name, O_RDWR);
	
	uint32_t len = filelength(name) / 4;
	//printf("length of file is %d\n", len);
	
	uint32_t* arr = (uint32_t*)malloc(len * sizeof(uint32_t));

	uint32_t num;
	
	uint32_t ptr = 0;

	while(read(fd, &num, sizeof(num)) > 0){
		arr[ptr++] = num;
	}
	qsort(arr, len, sizeof(uint32_t), cmpfunc);
	lseek(fd, 0, SEEK_SET);
	
	for(uint32_t i = 0; i < len; i++){
		write(fd, &arr[i], 4);		
	}
	free(arr);
	close(fd);
}

int main(int argc, char** argv){
	/*dont forget to open for reading and writing
	*/
	if(argc != 2){
		errx(1, "need exactly one argument");
	}
	/*
	shte imame 2 faila, v file1 zapisvame purvata polovina ot chislata
	vuv file 2 ostanalite. Sled tova sortirame vseki ot tqh sus qsort i nakraq 
	gi merge-vame v edin file 
	*/
	
	sort_file(argv[1]);
	exit(0);
}
