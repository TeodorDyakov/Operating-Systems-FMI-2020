#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

//Use this program so you can learn about text vs binary representation of data
//use a hex editor so you can inspect the files binary.bin and text.txt

char buf[8];
char id_str[8];

struct Student{
	char name[16];
	int id;
};

int main(int argc, char ** argv){
	
	//lets save the struct as binary
	struct Student student;
	student.id = 0xabcd;
	strcpy(student.name, "Teodor");

	int fd = open("binary.bin", O_WRONLY | O_CREAT, 0666);
	write(fd, &student, sizeof(student));
	close(fd);
	//ghex binary.bin and inspect the file
	//is the file human readable? which parts are and which are not? What if the name was in Cyrilic?
	//look at the the byte order for the id - is it big endian or little endian?
	
	//now lets the file read it back to student struct
	fd = open("binary.bin", O_RDONLY);
	read(fd, &student, sizeof(student));

	printf("name: %s\nid: %d\n", student.name, student.id);
	close(fd);

	//now lets save the student struct as readable text	
	fd = open("text.txt", O_RDWR | O_CREAT, 0666);
	write(fd, &student.name, strlen(student.name));
	write(fd, ",", 1);

	//convert the int idf to string
	sprintf(id_str, "%d", student.id);
	write(fd, &id_str, strlen(id_str));
	close(fd);

	//now lets read it back into student struct 
	fd = open("text.txt", O_RDONLY);
	read(fd, &student.name, strlen(student.name));
	char c;
	read(fd, &c, 1);
	read(fd, &buf, strlen(id_str));
	student.id = atoi(id_str);
	printf("name: %s\nid: %d\n", student.name, student.id);

}