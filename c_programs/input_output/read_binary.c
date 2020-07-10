#include<stdio.h> 
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<err.h>

/*
Напишете програма, която приема точно 2 аргумента. Първият може да бъде само --min, --max или --print (вижте man 3 strcmp). Вторият аргумент е двоичен файл, в който има записани цели неотрицателни двубайтови числа (uint16_t - вижте man stdint.h). Ако първият аргумент е:

--min - програмата отпечатва кое е най-малкото число в двоичния файл.
--max - програмата отпечатва кое е най-голямото число в двоичния файл.
--print - програмата отпечатва на нов ред всяко число.
*/

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
		uint16_t num = *(uint16_t *)(&buf);
		
		if(strcmp(argv[1], "--min") == 0){
			min = (min > num) ? num : min;		 		
		} else if(strcmp(argv[1], "--max") == 0){
			max = (max < num) ? num : max;
		} else { 						
			printf("%d\n", num);
		} 				
	}
		
	if(strcmp(argv[1], "--min") == 0){
		printf("min is %d\n", min);		 		
	} else if(strcmp(argv[1], "--max") == 0){
		printf("max is %d\n", max);
	}

	close(fd);
	exit(0);  
}
