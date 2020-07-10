#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdint.h>
#include<string.h>
#include<err.h>

int cmpfunc (const void* a, const void* b) {
	uint32_t num1 = *(uint32_t*)a;
	uint32_t num2 = *(uint32_t*)b;
	
	if(num1 < num2){
		return -1;
	}
		
	return num1 > num2 ? 1 : 0;
}

long filelength(char* path) {
 	struct stat st;
   	if(stat(path, &st))
	  	return -1;
   	return (long) st.st_size;
}

void sort_file(char *path){
	int fd = open(path, O_RDWR);
	uint32_t len = filelength(path);
	uint32_t* arr = (uint32_t*)malloc(len * sizeof(uint32_t));
	
	uint32_t idx = 0;
	
	while(read(fd, &arr[idx], 4) > 0){
		idx++;
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
	
	int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		
	if(fd == -1){
		exit(-1);
	}
	
	int arr[6] = {'h','e','l','l','a','o'};
	
	for(int i = 0; i < 6; i++){
		write(fd, &arr[i], 4);		
	}
	
	lseek(fd, 0, SEEK_SET);

	/*
	how many uint32_t are saved in the file;
	*/
	int len = filelength(argv[1]) / 4;
	
	int fd1 = open("tmp1", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if(fd1 == -1){
		err(1, "%s", "tmp1");
	}
	
	int fd2 = open("tmp2", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if(fd2 == -1){
		err(2, "%s", "tmp2");
	}
	
	
	int idx = 0;
	uint32_t num;
	
	// read the first half of the numbers and write them to tmp1
	for(; idx < len / 2; idx++){
		if(read(fd, &num, 4) > 0){
			write(fd1, &num, 4);	
		}	
	}

	// read the rest the numbers and write them to tmp2
	for(; idx < len; idx++){
		if(read(fd, &num, 4) > 0){
			write(fd2, &num, 4);	
		}	
	}
	close(fd1);
	close(fd2);

	
	sort_file("tmp1");
	sort_file("tmp2");

	fd1 = open("tmp1", O_RDONLY);
	if(fd1 == -1){
		err(1, "%s", "tmp1");
	}
	
	fd2 = open("tmp2", O_RDONLY);
	if(fd2 == -1){
		err(2, "%s", "tmp2");
	}

	
	uint32_t curr1 = 0, curr2 = 0;
	
	read(fd1, &curr1, 4);
	read(fd2, &curr2, 4);
	
	lseek(fd, 0, SEEK_SET);
	
	int read_cnt1 = 4, read_cnt2 = 4;
	while((read_cnt1 == 4) && (read_cnt2 == 4)){
		if(curr1 > curr2){
			write(fd, &curr2, 4);
			read_cnt2 = read(fd2, &curr2, 4);
		} else{
			write(fd, &curr1, 4);
			read_cnt1 = read(fd1, &curr1, 4);
		}
	}
	
	while(read(fd1, &curr1, 4) == 4){
		write(fd, &curr1, 4);
	}
	
	while(read(fd2, &curr2, 4) == 4){
		write(fd, &curr2, 4);
	}
	
	close(fd);
	close(fd1);
	close(fd2);	
	
	exit(0);
}
