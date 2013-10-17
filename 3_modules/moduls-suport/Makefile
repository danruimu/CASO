
ifneq ($(KERNELRELEASE),)

 # for kbuild

obj-m := mymodule.o
mymodule-y := interface.o implementation.o

else

 # normal Makefile

KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD

endif

