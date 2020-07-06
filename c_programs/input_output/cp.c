#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char* argv[])
{
	if (argc != 3) {
		errx(1, "err");
	}

	int fd1;
	fd1 = open(argv[1], O_RDWR);
	if (fd1 == -1) {
		err(2, "%s", argv[1]);
	}

	int fd2;
	fd2 = open(argv[2], O_CREAT | O_RDWR | O_TRUNC);
	if (fd2 == -1) {
		close(fd1);
		err(3, "%s", argv[2]);
	}

	char c;
	int read_cnt;
	
	while ((read_cnt = read(fd1, &c, sizeof(c))) > 0) {
		if(read_cnt != write(fd2, &c, sizeof(c))){
			errx(4, "err");
		}
	}
	
	close(fd1);
	close(fd2);

	exit(0);
}
