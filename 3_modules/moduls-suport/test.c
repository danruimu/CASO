#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void main(int argc, char *argv[]) {
	if(argc != 2) {
		fprintf(stderr, "USAGE: %s N\n", argv[0]);
		fprintf(stderr, "\tN:\t Numbers of characters to read\n");
		exit(1);
	}

	int n = atoi(argv[1]);
	
	int fd = open("/dev/mymodule", O_RDONLY);
	char *buffer = (char*) malloc(n);
	
	int res = read(fd, (void*) buffer, n);
	if(res != n) {
		fprintf(stdout, "res = %d and buffer=%d\n", res, atoi(buffer));
	}
	while(1) sleep(1000);
}
