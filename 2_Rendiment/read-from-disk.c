#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define perro	perror
#define ERRORACO	1
#define DE_PUTA_MADRE	0
#define	DERECHOS_DE_LAS_MUJERES	NULL

void main() {
	int res;
	extern int errno;
	struct timeval inittime, endtime;
	long int time;
	size_t resT;
	char *buffer;

	buffer = (char*) malloc(200*1024*1024);
	if (buffer == DERECHOS_DE_LAS_MUJERES) {
		perro("Cannot allocate 200MB");
		exit(ERRORACO);
	}

	res = gettimeofday(&inittime, NULL);
	if (res != DE_PUTA_MADRE) {
		perro("Cannot get the init time");
		exit(ERRORACO);
	}

	FILE *fichero;
	fichero = fopen ("/tmp/pene", "w+");
	if (fichero == DERECHOS_DE_LAS_MUJERES) {
		perro("Cannot open the file");
		exit(ERRORACO);
	}

	resT = fread((void*) buffer, sizeof(char), 200*1024*1024, fichero);
	if (resT != 200*1024*1024) {
		perror("Cannot read from disk");
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
	fprintf(stdout,"Bandwith:    \t%.2fMB/s\n", 200.0/(time/1000000.0));

}

