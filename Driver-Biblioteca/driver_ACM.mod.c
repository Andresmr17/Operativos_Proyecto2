#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_MITIGATION_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif



static const char ____versions[]
__used __section("__versions") =
	"\x10\x00\x00\x00\x7e\x3a\x2c\x12"
	"_printk\0"
	"\x1c\x00\x00\x00\xca\x39\x82\x5b"
	"__x86_return_thunk\0\0"
	"\x20\x00\x00\x00\x9f\x62\xb0\x40"
	"tty_unregister_driver\0\0\0"
	"\x20\x00\x00\x00\xb8\xcd\x2f\xdc"
	"tty_unregister_device\0\0\0"
	"\x1c\x00\x00\x00\xc8\x1b\x50\x12"
	"tty_port_destroy\0\0\0\0"
	"\x10\x00\x00\x00\xba\x0c\x7a\x03"
	"kfree\0\0\0"
	"\x14\x00\x00\x00\x7c\x46\xa4\x7a"
	"usb_put_dev\0"
	"\x14\x00\x00\x00\x60\xf9\x84\x98"
	"_dev_info\0\0\0"
	"\x18\x00\x00\x00\x31\xe1\x34\x72"
	"usb_deregister\0\0"
	"\x1c\x00\x00\x00\x63\xa5\x03\x4c"
	"random_kmalloc_seed\0"
	"\x18\x00\x00\x00\x98\x04\xd2\xf2"
	"kmalloc_caches\0\0"
	"\x20\x00\x00\x00\xfe\x6e\xe0\xb2"
	"__kmalloc_cache_noprof\0\0"
	"\x14\x00\x00\x00\xee\xf9\xf8\xe0"
	"usb_get_dev\0"
	"\x18\x00\x00\x00\xfa\x4a\xd8\xd3"
	"tty_port_init\0\0\0"
	"\x24\x00\x00\x00\x05\x8c\x81\xc1"
	"tty_port_register_device\0\0\0\0"
	"\x1c\x00\x00\x00\x91\xc9\xc5\x52"
	"__kmalloc_noprof\0\0\0\0"
	"\x14\x00\x00\x00\x0c\x5b\x5a\x17"
	"_dev_err\0\0\0\0"
	"\x14\x00\x00\x00\xbb\x6d\xfb\xbd"
	"__fentry__\0\0"
	"\x1c\x00\x00\x00\x68\xbf\xcd\x2a"
	"__tty_alloc_driver\0\0"
	"\x18\x00\x00\x00\xc1\x7e\xb2\x67"
	"tty_std_termios\0"
	"\x1c\x00\x00\x00\x47\x72\xdd\x5a"
	"tty_register_driver\0"
	"\x1c\x00\x00\x00\x3a\x81\xfa\xaf"
	"usb_register_driver\0"
	"\x18\x00\x00\x00\x34\x61\x23\x68"
	"module_layout\0\0\0"
	"\x00\x00\x00\x00\x00\x00\x00\x00";

MODULE_INFO(depends, "");

MODULE_ALIAS("usb:v2A03p0043d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "738760A0F17C77064FA13CB");
