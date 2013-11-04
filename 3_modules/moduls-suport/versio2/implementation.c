
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>

int implementation (int arg)
{
   return 0;
}

//int nOpen = 0;
//
//static int obrir(struct inode * inode, struct file * file) {
//	nOpen++;
//	printk("Opened too many times!!!\nNot really, only %d times :-)\n", nOpen);
//	if(imajor(inode) != 230 || iminor(inode) != 3) {
//		printk("Error!!! The major and minor don't match!!\n");
//		return -42;
//	}
//	return 0;
//}
//
//static int tancar(struct inode * inode, struct file * file) {
//	nOpen--;
//	printk("Closed too many times!!!\nNot really, only %d times :-)\n", nOpen);
//	if(imajor(inode) != 230 || iminor(inode) != 3) {
//		printk("Error!!! The major and minor don't match!!\n");
//		return -42;
//	}
//	return 0;
//
//}
//
//static ssize_t llegir(struct file * file, char __user * buffer,size_t size, loff_t * offset) {
//	if(sizeof(nOpen) <= size) {
//		*buffer = nOpen;
//		return sizeof(nOpen);
//	}
//	return -42;
//}
