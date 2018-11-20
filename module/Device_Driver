obj-m = mod.o hello.o

KDIR=/lib/modules/$(shell uname -r)/build #/lib/modules/4.14.78-v7+/build connect
PWD:=$(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf *.o *.ko *.mod.c .mod.* Module.syvers modules.order
