#include<stdlib.h>
#include<unistd.h>
#include<err.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, char ** argv){
	if(argc != 2){
		errx(3, "err");
	}
	
	int fd = open(argv[1], O_RDONLY);

	if(fd == -1){
		err(1, "%s", argv[1]);
	}
	
	char buf[4096];
	int read_cnt;
	
	while((read_cnt = read(fd, &buf, sizeof(buf))) > 0){
		
		if(read_cnt != write(1, &buf, sizeof(buf))){
			err(2, "error");
		}
	}
	
	close(fd);
	exit(0);
		
}
