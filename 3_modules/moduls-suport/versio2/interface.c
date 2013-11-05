#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

#define MY_MAJOR 230

#define MAX_IDS 500
#define BUFF_SIZE 4096
#define SET_STRING_ID 13
#define GET_STRING_ID 17

MODULE_LICENSE("Dual BSD/GPL");
static int nOpen = 0;
static unsigned int currentBuffer = 0;
static char *bufferChar[MAX_IDS];

static int obrir(struct inode * inode, struct file * file) {
	nOpen++;
	printk("Opened too many times!!!\nNot really, only %d times :-)\n", nOpen);
	if(imajor(inode) != 230 || iminor(inode) != 3) {
		printk("Error!!! The major and minor don't match!!\n");
		return -42;
	}
	return 0;
}

static int tancar(struct inode * inode, struct file * file) {
	nOpen--;
	printk("Closed too many times!!!\nNot really, only %d times :-)\n", nOpen);
	if(imajor(inode) != 230 || iminor(inode) != 3) {
		printk("Error!!! The major and minor don't match!!\n");
		return -42;
	}
	return 0;

}

static ssize_t llegir(struct file * file, char __user * buffer,size_t size, loff_t * offset) {
	long res;
	int offs;
	offs = *offset;
	res = copy_to_user(buffer, &bufferChar[currentBuffer][offs], (long unsigned int) size);
	if(res != 0) {
		printk(KERN_DEBUG "[ERROR] LLEGIR: No s'han copiat %ld de %ld\n", res, size);
		return -EFAULT;
	}
	return (ssize_t) size - res;
}

static ssize_t escriure(struct file * file, const char __user * buffer, size_t size, loff_t * offset) {
	long res;
	int offs;
	offs = *offset;
	if(bufferChar[currentBuffer] == NULL ) {
		bufferChar[currentBuffer] = (char *) kzalloc(size, GFP_KERNEL);
	}
   	res = copy_from_user(&bufferChar[currentBuffer][offs], buffer, (long unsigned int) size);
	if(res != 0) {
		printk(KERN_DEBUG "[ERROR] ESCRIURE: No s'han copiat %ld de %ld\n", res, size);
		return -EFAULT;
	}
	return (ssize_t) size - res;
}

static long control(struct file * file, unsigned int command, unsigned long argument) {
	if(command != SET_STRING_ID && command != GET_STRING_ID) {
		return -42;
	}
	if(argument > MAX_IDS) {
		return -42;
	}
	if(command == SET_STRING_ID) currentBuffer = argument;
	else if(command == GET_STRING_ID) return currentBuffer;
	return 0;
}

static const struct file_operations operacions = {
	.owner          = THIS_MODULE,
	.open			= obrir,
	.release		= tancar,
	.read			= llegir,
	.write			= escriure,
	.unlocked_ioctl	= control,
};

static int mymodule_init(void) {
	int res;
	unsigned int i;
	res = register_chrdev (MY_MAJOR, "CASO chardrv", &operacions);
	if (res < 0) {
  		printk(KERN_DEBUG "Error registering the module\n");
		return res;
	}
	for(i = 0; i<MAX_IDS; ++i) {
		bufferChar[i] = NULL;
	}
  printk(KERN_DEBUG "Hello world!\n");
  return 0;
}

static void mymodule_exit(void) {
	unsigned int i;
	for(i = 0; i<MAX_IDS; ++i) {
		kfree((const void*) bufferChar[i]);
	}
	unregister_chrdev(MY_MAJOR, "CASO chardrv");
  printk(KERN_DEBUG "Bye, cruel world\n");
}

module_init(mymodule_init);
module_exit(mymodule_exit);
