#include<unistd.h>
#include<fcntl.h>
#include<err.h>
#include <sys/types.h>
#include <sys/stat.h>

/*

*/

int main(int argc, char** argv){
	mkfifo("fifo", S_IRUSR | S_IWUSR);
	int fd = open("fifo", O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1){
		err(1, "fifo");
	}
	if(dup2(fd, 1) == -1){
		errx(1, "error in dup2");
	}
	execlp(argv[1], "", NULL);			
}
