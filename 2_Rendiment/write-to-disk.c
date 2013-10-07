#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define perro	perror
#define ERRORACO	1
#define DE_PUTA_MADRE	0
#define	DERECHOS_DE_LAS_MUJERES	NULL

void main(int argc, char *argv[]) {
	int res;
	extern int errno;
	struct timeval inittime, endtime;
	long int time;
	size_t resT;
	char *buffer;
	char *file;
	size_t size;

	if (argc != 3) {
		fprintf(stderr, "USAGE: %s [FILE] [SIZE_MB]\n", argv[0]);
		exit(1);
	}

	file = argv[1];
	size = (size_t) atoi(argv[2]);
	fprintf(stdout, "Writing a %zuMB file at %s\n", size, file);

	buffer = (char*) malloc(size*1024*1024);
	if (buffer == DERECHOS_DE_LAS_MUJERES) {
		perro("Cannot allocate enough memory");
		exit(ERRORACO);
	}

	buffer = (char*) memset(buffer, 0, size*1024*1024);
	if (buffer == DERECHOS_DE_LAS_MUJERES) {
		perro("Cannot set buffer to 1");
		exit(ERRORACO);
	}

	res = gettimeofday(&inittime, NULL);
	if (res != DE_PUTA_MADRE) {
		perro("Cannot get the init time");
		exit(ERRORACO);
	}

	FILE *fichero;
	fichero = fopen (file, "w+");
	if (fichero == DERECHOS_DE_LAS_MUJERES) {
		perro("Cannot open the file");
		exit(ERRORACO);
	}

	resT = fwrite((void*) buffer, sizeof(char), size*1024*1024, fichero);
	if (resT != size*1024*1024) {
		perror("Cannot write to disk");
		exit(ERRORACO);
	}

	res = fclose (fichero);
	if (res != DE_PUTA_MADRE) {
		perro("Cannot close the file");
		exit(ERRORACO);
	}
	
	res = gettimeofday(&endtime, NULL);
	if (res != DE_PUTA_MADRE) {
		perro("Cannot get the end time");
		exit(ERRORACO);
	}

	time = (endtime.tv_usec+endtime.tv_sec*1000000) - (inittime.tv_usec+inittime.tv_sec*1000000);

	fprintf(stdout,"Time elapsed:\t%.3fms\n",time/1000.0);
	fprintf(stdout,"Bandwith:    \t%.2fMB/s\n", size/(time/1000000.0));

}

