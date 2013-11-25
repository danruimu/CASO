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
	{ 0x7dc216d9, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xdf08d9a5, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x2fb43771, __VMLINUX_SYMBOL_STR(alloc_disk) },
	{ 0xb258fbfd, __VMLINUX_SYMBOL_STR(blk_cleanup_queue) },
	{ 0x4c4fef19, __VMLINUX_SYMBOL_STR(kernel_stack) },
	{ 0xd6ee688f, __VMLINUX_SYMBOL_STR(vmalloc) },
	{ 0x15692c87, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x3a9b6fb9, __VMLINUX_SYMBOL_STR(blk_unregister_region) },
	{ 0x364b6240, __VMLINUX_SYMBOL_STR(blk_queue_max_hw_sectors) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x6cbc6fbe, __VMLINUX_SYMBOL_STR(blk_alloc_queue) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xe91d17ad, __VMLINUX_SYMBOL_STR(del_gendisk) },
	{ 0xc3ddd530, __VMLINUX_SYMBOL_STR(blk_register_region) },
	{ 0x71a50dbc, __VMLINUX_SYMBOL_STR(register_blkdev) },
	{ 0x8d947573, __VMLINUX_SYMBOL_STR(get_disk) },
	{ 0x31ed1403, __VMLINUX_SYMBOL_STR(bio_endio) },
	{ 0xb5a459dc, __VMLINUX_SYMBOL_STR(unregister_blkdev) },
	{ 0xc88c4abe, __VMLINUX_SYMBOL_STR(blk_queue_bounce_limit) },
	{ 0xe34a2827, __VMLINUX_SYMBOL_STR(blk_queue_make_request) },
	{ 0x1213e4f3, __VMLINUX_SYMBOL_STR(put_disk) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
	{ 0xa6327d27, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x69acdf38, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xb4d9904e, __VMLINUX_SYMBOL_STR(add_disk) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "02547F484844E0381F2BB60");
