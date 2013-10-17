#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("Dual BSD/GPL");

static int mymodule_init(void) {
  printk(KERN_DEBUG "Hello world!\n");
  return 0;
}

static void mymodule_exit(void) {
  printk(KERN_DEBUG "Bye, cruel world\n");
}

module_init(mymodule_init);
module_exit(mymodule_exit);
