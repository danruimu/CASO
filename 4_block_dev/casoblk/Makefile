
ifneq ($(KERNELRELEASE),)

 # for kbuild

obj-m := myblkdrv.o
myblkdrv-y := interface.o implementation.o

else

 # normal Makefile

KDIR ?= /lib/modules/`uname -r`/build

default:
	$(MAKE) -C $(KDIR) M=$$PWD

endif

clean:
	rm -rf implementation.o  interface.o myblkdrv.o myblkdrv.mod.o \
            myblkdrv.ko built-in.o myblkdrv.mod.c Module.symvers modules.order .*.cmd .tmp_versions

