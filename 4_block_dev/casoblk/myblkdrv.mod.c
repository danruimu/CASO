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
	{ 0x92bb2bf4, "module_layout" },
	{ 0x561a2460, "kmalloc_caches" },
	{ 0x54768459, "alloc_disk" },
	{ 0x84d1f62e, "blk_cleanup_queue" },
	{ 0x4c4fef19, "kernel_stack" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0x15692c87, "param_ops_int" },
	{ 0x3a9b6fb9, "blk_unregister_region" },
	{ 0x75e7be12, "blk_queue_max_hw_sectors" },
	{ 0x999e8297, "vfree" },
	{ 0x91715312, "sprintf" },
	{ 0xaaf94217, "blk_alloc_queue" },
	{ 0x27e1a049, "printk" },
	{ 0x6fc4c0be, "del_gendisk" },
	{ 0x7beab23d, "blk_register_region" },
	{ 0x71a50dbc, "register_blkdev" },
	{ 0xf0eb09b3, "get_disk" },
	{ 0x74b398b2, "bio_endio" },
	{ 0xb5a459dc, "unregister_blkdev" },
	{ 0xbcd0a058, "blk_queue_bounce_limit" },
	{ 0x79075379, "blk_queue_make_request" },
	{ 0xcc7b9ef1, "put_disk" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xe55dd87c, "kmem_cache_alloc_trace" },
	{ 0x37a0cba, "kfree" },
	{ 0x69acdf38, "memcpy" },
	{ 0x32828852, "add_disk" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "B01B7E4028B2365EA3E36CC");
