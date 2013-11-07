#include <linux/blkdev.h>

#include <linux/kernel.h>
#include <linux/genhd.h>
#include <linux/hdreg.h>

#include <linux/vmalloc.h>

#include "interface.h"


char * alloc_disk_memory(unsigned long size)
{
   char * p = NULL;
   unsigned long i;

   // la vostra implementacio va aqui
   	if(size > XRD_SIZE*1024) {
		return -ENOMEM;
	}
	p = vmalloc(PAGE_ALIGN(size));
	for(i = 0; i<size; ++i) p[i] = i%256;
   // fi de la vostra implementacio

   printk(KERN_DEBUG "alloc_disk_memory %ld address %p\n", size, p);
   // retorna el punter a la memoria del kernel per guardar les dades del disc
   return p;
}

void   free_disk_memory(char * disk_mem)
{
	unsigned int i;
	char exists = 0;
   // la vostra implementacio va aqui
	for(i=0; i<MAX_XRD && !exists; ++i) {
		if(xrd_array[i]->disk_memory == disk_mem) exists=1;
	}
	vfree((const void*) disk_mem;
   // fi de la vostra implementacio
   printk(KERN_DEBUG "free_disk_memory %p\n", disk_mem);
}


int xrd_getgeo(struct block_device * bdev, struct hd_geometry *geo)
{
   int res = -EIO;

   // la vostra implementacio va aqui


   // fi de la vostra implementacio

   // un resultat = 0 indica tot correcte
   printk (KERN_DEBUG "xrd_getgeo returns %d", res);
   return res;
}


int copy_from_xrd(void *dst, struct xrd_struct *xrd,
                        sector_t sector, size_t n)
{
   int res = -ENODEV;

   // la vostra implementacio va aqui




   // fi de la vostra implementacio

   printk(KERN_DEBUG "copy_from_xrd retorna %d\n", res);
   // un resultat = 0 indica tot correcte
   return res;
}

int copy_to_xrd(struct xrd_struct *xrd, void *src,
                        sector_t sector, size_t n)
{
   int res = -ENODEV;
   
   // la vostra implementacio va aqui




   // fi de la vostra implementacio

   printk(KERN_DEBUG "copy_to_xrd retorna %d\n", res);
   // un resultat = 0 indica tot correcte
   return res;
}


