#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

#define MY_MAJOR 230

MODULE_LICENSE("Dual BSD/GPL");
static int nOpen = 0;

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
	if(sizeof(nOpen) <= size) {
		//*buffer = nOpen;
		sprintf(buffer, "%d", nOpen);
		return sizeof(nOpen);
	}
	return -42;
}

static const struct file_operations operacions = {
	.owner          = THIS_MODULE,
	.open			= obrir,
	.release		= tancar,
	.read			= llegir
};

static int mymodule_init(void) {
	int res;
	res = register_chrdev (MY_MAJOR, "PENE de CASO", &operacions);
	if (res < 0) {
  		printk(KERN_DEBUG "Error registering the module\n");
		return res;
	}
  printk(KERN_DEBUG "Hello world!\n");
  return 0;
}

static void mymodule_exit(void) {
	unregister_chrdev(MY_MAJOR, "PENE de­CASO");
  printk(KERN_DEBUG "Bye, cruel world\n");
}

module_init(mymodule_init);
module_exit(mymodule_exit);
