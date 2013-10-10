#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


int main(int argc, char * argv [])
{
   intptr_t increment = 0;
   int res;
   void *p;
   struct timeval tv0, tv1;
   double secs;
   int n = 2, i;

   //if (argc < 2) {
   //   fprintf(stderr, "Us: %s [size]\n", argv[0]);
   //   exit(1);
   //}


   res = gettimeofday(&tv0, NULL);
   if (res < 0) { 
      perror ("gettimeofday");
   }

   for (i=0; i < n; i++) {
      res = sleep(1);
      if (res < 0) {
         perror ("sleep");
      }
   }

   res = gettimeofday(&tv1, NULL);
   if (res < 0) {
      perror ("gettimeofday");
   }
   secs = (((double)tv1.tv_sec*1000000.0 + (double)tv1.tv_usec) - 
          ((double)tv0.tv_sec*1000000.0 + (double)tv0.tv_usec))/1000000.0;

   printf ("    %lf s. (%le s/sleep)\n", secs, secs / n );

}
