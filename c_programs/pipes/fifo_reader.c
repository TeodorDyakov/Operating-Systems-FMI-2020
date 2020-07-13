#include<unistd.h>
#include<fcntl.h>
#include<err.h>
#include <sys/types.h>
#include <sys/stat.h>

/*

*/

int main(int argc, char** argv){
	int fd = open("fifo", O_RDONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1){
		err(1, "fifo");
	}
	if(dup2(fd, 0) == -1){
		errx(1, "error in dup2");
	}
	execlp(argv[1], "", NULL);			
}
