
ifneq ($(KERNELRELEASE),)

 # for kbuild

obj-m := mychardrv.o
mychardrv-y := interface.o implementation.o

else

 # normal Makefile

KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD

endif
