#include <stdio.h>
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char* argv[])
{
	int fd = open("/etc/passwd", O_RDONLY);

	if(fd == -1){
		err(1, "failed to open file");	
	}
	
	int passwd_copy = open("passwd", O_CREAT | O_WRONLY);
	
	char buf[4096];
	int read_cnt = 0;
	
	while(read_cnt = read(fd, &buf, 1)){
		
		for(int i = 0; i < read_cnt; i++){
			if(buf[i] == ':'){
				buf[i] = '?';
			}
		}
		
		if(read_cnt != write(passwd_copy, &buf, 1)){
			err(2, "error in writing!\n");
		}	
	}

	exit(0);
}
