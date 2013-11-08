#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <string.h>

#include "file_string_user.h"


int buf [4096];
char cbuf[1024];


int main()
{
   char * memory;
   int res, i;
   int fd = open ("./mychardrv", O_RDWR, 0);
   if(fd == -1) {
	  perror("Error opening the device");
	  exit(0);
   }

#if 0
   int fd2;
   if (fd < 0) {
      perror ("open");
      exit(1);
   }
#endif



   res = ioctl (fd, GET_STRING_ID, 0);
   if(res == -1) {
		perror("Bad string id");
		exit(-1);
   }
   printf("current string id %d\n", res);

   res = read(fd, buf, 4096);
   if (res < 0) perror ("read");
   if (res < sizeof(int)) printf ("Expected %d bytes, got %d\n", (int)sizeof(int), res);
   printf ("Got %d opens\n", buf[0]);

   res = ioctl (fd, SET_STRING_ID, 9);
   if (res < 0) perror ("ioctl SET_STRING_ID");

   res = write(fd, "Hi, this is a first test\n", 26);
   if (res < 0) perror ("write");
   printf ("Written %d bytes to the file\n", res);

   res = write(fd, "Hi, this is a second test\n", 27);
   if (res < 0) perror ("write");
   printf ("Written %d bytes to the file\n", res);

   for (i=0; i < 100; i++) cbuf[i] = 'a';

   res = read(fd, cbuf, 10);
   if (res < 0) perror ("read");
   else {
      cbuf[res] = '\0';
      printf ("Read '%s' (%d bytes)\n", cbuf, res);
   }

   for (i=0; i < 100; i++) cbuf[i] = 'a';
   res = read(fd, cbuf, 26);
   if (res < 0) perror ("read");
   else {
      cbuf[res] = '\0';
      printf ("Read '%s' (%d bytes)\n", cbuf, res);
   }

   for (i=0; i < 100; i++) cbuf[i] = 'a';
   res = read(fd, cbuf, 27);
   if (res < 0) perror ("read");
   else {
      cbuf[res] = '\0';
      printf ("Read '%s' (%d bytes)\n", cbuf, res);
   }
   
   for (i=0; i < 100; i++) cbuf[i] = 'a';
   res = read(fd, cbuf, 28);
   if (res < 0) perror ("read");
   else {
      cbuf[res] = '\0';
      printf ("Read '%s' (%d bytes)\n", cbuf, res);
   }
   

   res = ioctl (fd, SET_STRING_ID, 91);
   if (res < 0) perror ("ioctl SET_STRING_ID");
   
   memory = mmap((void *)0x100000000000, getpagesize(), PROT_READ | PROT_WRITE, 
                       MAP_FIXED | MAP_ANONYMOUS | MAP_PRIVATE,
                       -1, 0L);
   if (memory == (void *) -1) {
      perror ("mmap");
      exit(1);
   }
   printf ("memory at %lx\n", (long unsigned int) memory);

//   memory[4096] = 0;
   
   strcpy (&memory[4090], "hola ");
   res = write(fd, &memory[4090], 27);
   if (res < 0) perror ("write");
   printf ("Written %d bytes to the file\n", res);

   for (i=0; i < 100; i++) cbuf[i] = 'a';
   res = read(fd, cbuf, 28);
   if (res < 0) perror ("read");
   else {
      cbuf[res] = '\0';
      printf ("Read '%s' (%d bytes)\n", cbuf, res);
   }
   
#if 0
   fd2 = open ("myfile.txt", O_RDWR | O_TRUNC | O_CREAT, 0664);
   if (fd2 < 0) {
      perror ("open");
      exit(1);
   }
   res = write(fd2, &memory[4090], 27);
   if (res < 0) perror ("write to file");
   printf ("Written %d bytes to the file\n", res);
   lseek(fd2, 0, SEEK_SET);

   for (i=0; i < 100; i++) cbuf[i] = 'a';
   res = read(fd2, cbuf, 28);
   if (res < 0) perror ("read");
   else {
      cbuf[res] = '\0';
      printf ("Read '%s' (%d bytes)\n", cbuf, res);
   }
#endif


   res = ioctl (fd, SET_STRING_ID, 9);
   if (res < 0) perror ("ioctl SET_STRING_ID");
   

   for (i=0; i < 100; i++) cbuf[i] = 'a';
   res = read(fd, cbuf, 28);
   if (res < 0) perror ("read");
   else {
      cbuf[res] = '\0';
      printf ("Read '%s' (%d bytes)\n", cbuf, res);
   }
   
   
 

   close(fd);


}
