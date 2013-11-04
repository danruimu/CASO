#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
<<<<<<< HEAD
	{ 0xfb075172, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x6bc3fbc0, __VMLINUX_SYMBOL_STR(__unregister_chrdev) },
	{ 0xea9a7989, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x18f758d4, __VMLINUX_SYMBOL_STR(__register_chrdev) },
	{ 0x4f8b5ddb, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
	{ 0x2a63cd39, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x4f6b400b, __VMLINUX_SYMBOL_STR(_copy_from_user) },
=======
	{ 0x92bb2bf4, "module_layout" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0xd2b09ce5, "__kmalloc" },
	{ 0x848237df, "__register_chrdev" },
	{ 0x4f8b5ddb, "_copy_to_user" },
	{ 0x27e1a049, "printk" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x37a0cba, "kfree" },
	{ 0x4f6b400b, "_copy_from_user" },
>>>>>>> 759f3e3ac3a294db65368fdd6f7a06429d6b67f2
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

<<<<<<< HEAD
=======

MODULE_INFO(srcversion, "F2D910882A6DA8F4D6EB2E8");
>>>>>>> 759f3e3ac3a294db65368fdd6f7a06429d6b67f2
