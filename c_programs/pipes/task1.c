#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<wait.h>
#include<err.h>
#include<errno.h>

int main(int argc, char** argv){
	if(argc != 2){
		errx(1, "usage %s <string>", argv[0]);
	}
	int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if(fd == -1){
		err(1, "%s", argv[1]);
	}
	
	const char* str1 = "foo\n";
	const char* str2 = "bar\n";
	
	if(write(fd, str1, 2) != 2){
		const int saved_errno = errno;
		close(fd);
		errno = saved_errno;
		errx(1, "error in writing");
	}
		
}

