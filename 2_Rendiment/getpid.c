#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define	N	1000000

void main () {
	unsigned int i;
	int res;
	pid_t pid;
	struct timeval init, end;
	double secs;

	res = gettimeofday(&init, NULL);
	if (res < 0) {
		perror("gettimeofday INIT");
		exit(1);
	}

	for(i=0; i < N; i++) {
		pid = getpid();
	}

	res = gettimeofday(&end, NULL);
	if (res < 0) {
		perror("gettimeofday END");
		exit(1);
	}

	secs = (((double) end.tv_sec*1000000.0 + (double) end.tv_usec) - ((double) init.tv_sec*1000000.0 + (double) init.tv_usec))/1000000.0;

	fprintf(stdout, "%lf s. (%le s/getpid)\n", secs, secs / N);
}
