#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdio.h>

//Use thi program so you can learn abou text vs binary
//use a hex editor so you can inspect the the files binary.bin and text.txt

char buf[8];
char str[8];

int main(int argc, char ** argv){
	
	int fd = open("binary.bin", O_WRONLY | O_CREAT, 0666);

	const int num = 0xabcd;

	write(fd, &num, sizeof(num));
	close(fd);

	fd = open("binary.bin", O_RDONLY);
	int rd = 0;
	read(fd, &rd, sizeof(rd));

	printf("Number read from binary.bin file as int: %d\n", rd);
	close(fd);

	sprintf(str, "%d", num);
	fd = open("text.txt", O_RDWR | O_CREAT, 0666);
	write(fd, str, sizeof(str));
	close(fd);

	fd = open("text.txt", O_RDONLY);
	rd = 0;
	read(fd, &rd, sizeof(rd));
	printf("Number read from text.txt as int: %d\n", rd);
	close(fd);

	fd = open("text.txt", O_RDONLY);

	read(fd, &buf, sizeof(buf));

	printf("Number read from text.txt as text: %s\n", buf);
	close(fd);
}