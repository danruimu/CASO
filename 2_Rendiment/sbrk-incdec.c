#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define	N	1000000

void main () {
	unsigned int i;
	int res;
	void *p;
	struct timeval init, end;
	double secs;
	intptr_t inc = 8192*2;

	res = gettimeofday(&init, NULL);
	if (res < 0) {
		perror("gettimeofday INIT");
		exit(1);
	}

	for(i=0; i < N; i++) {
		p = sbrk(inc);
		if (p == (void *) -1) {
			perror("sbrk");
			exit(1);
		}
	}

	res = gettimeofday(&end, NULL);
	if (res < 0) {
		perror("gettimeofday END");
		exit(1);
	}

	secs = (((double) end.tv_sec*1000000.0 + (double) end.tv_usec) - ((double) init.tv_sec*1000000.0 + (double) init.tv_usec))/1000000.0;

	fprintf(stdout, "Increment = %d\n", (int) inc);
	fprintf(stdout, "%lf s. (%le s/sbrk)\n", secs, secs / N);
}
