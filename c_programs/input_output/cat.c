#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char* argv[]){

	for(int i = 1; i < argc; i++){

		int fd = open(argv[i], O_RDONLY);

		if( fd == -1){
			err(99, "error in opening file");
		}

		char c;

		while(read(fd, &c, 1)){
			write(0, &c, 1);
		}

		close(fd);
	}

	exit(0);
}
