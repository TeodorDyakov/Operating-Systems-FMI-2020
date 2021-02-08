#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdio.h>

//Use thi program so you can learn abou text vs binary
//use a hex editor so you can inspect the the files binary.bin and text.txt

int main(int argc, char ** argv){
	
	int fd = open("binary.bin", O_WRONLY | O_CREAT, 0666);

	const int num = 0xabcd;

	write(fd, &num, sizeof(num));
	close(fd);

	fd = open("binary.bin", O_RDONLY);
	int rd = 0;
	read(fd, &rd, sizeof(rd));

	printf("Number read from binary.bin file: %d\n", rd);
	close(fd);
	
	char str[8];
	for(int i = 0; i < 8; i++){
		str[i] = '\0';
	}

	sprintf(str, "%d", num);
	fd = open("text.txt", O_RDWR | O_CREAT, 0666);
	write(fd, str, sizeof(str));
	close(fd);

	fd = open("text.txt", O_RDONLY);
	rd = 0;
	read(fd, &rd, sizeof(rd));
	printf("Number read from text.txt: %d\n", rd);
	close(fd);
}