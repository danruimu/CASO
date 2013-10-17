#include <stdio.h>
#include <sys/file.h>
#include <sys/mman.h>

#include "file_string_user.h"


//int buf [4096];
char cbuf[1024];


int main()
{
   char * memory;
   int res, i;
   int fd = open ("mychardrv", O_RDWR, 0);

   res = ioctl (fd, SET_STRING_ID, 1);
   if (res < 0) perror ("ioctl SET_STRING_ID");

   res = write(fd, "Hi, this is a first test\n", 26);
   if (res < 0) perror ("write");

   res = ioctl (fd, SET_STRING_ID, 2);
   if (res < 0) perror ("ioctl SET_STRING_ID");

   res = write(fd, "Hi, this is a second test\n", 27);
   if (res < 0) perror ("write");

   res = ioctl (fd, SET_STRING_ID, 1);
   if (res < 0) perror ("ioctl SET_STRING_ID");

   res = read(fd, cbuf, 10);
   if (res < 0) perror ("read");
   else {
      cbuf[res] = '\0';
      printf ("Read from ID 1: '%s' (%d bytes)\n", cbuf, res);
   }

   res = ioctl (fd, SET_STRING_ID, 2);
   if (res < 0) perror ("ioctl SET_STRING_ID");

   res = read(fd, cbuf, 100);
   if (res < 0) perror ("read");
   else {
      cbuf[res] = '\0';
      printf ("Read from ID 2: '%s' (%d bytes)\n", cbuf, res);
   }

   close(fd);
}
