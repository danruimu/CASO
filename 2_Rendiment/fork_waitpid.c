#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define	N	1000

void main () {
	unsigned int i;
	int res, status;
	pid_t pid;
	struct timeval init, end;
	double secs;

	res = gettimeofday(&init, NULL);
	if (res < 0) {
		perror("gettimeofday INIT");
		exit(1);
	}

	for(i=0; i < N; i++) {
		pid = fork();
		if (pid ==  0) {	//CHILD
			exit(0);
		} else if (pid == -1) {	//PARENT ON ERROR
			perror ("fork");
			exit(1);
		} else {	//PARENT
			pid = waitpid(-1, &status, 0);
			if (pid == -1) {
				perror("waitpid");
				exit(1);
			}
		}
	}

	res = gettimeofday(&end, NULL);
	if (res < 0) {
		perror("gettimeofday END");
		exit(1);
	}

	secs = (((double) end.tv_sec*1000000.0 + (double) end.tv_usec) - ((double) init.tv_sec*1000000.0 + (double) init.tv_usec))/1000000.0;

	fprintf(stdout, "%lf s. (%le s/fork_waitpid)\n", secs, secs / N);
}
