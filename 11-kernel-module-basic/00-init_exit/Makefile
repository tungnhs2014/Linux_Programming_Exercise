<<<<<<< Updated upstream
# Hello world kernel module

EXTRA_CFLAGS = -Wall
obj-m = hello.o

KDIR = /lib/modules/`uname -r`/build

all:
	make -C $(KDIR) M=`pwd` modules

clean:
=======
# Hello world kernel module

EXTRA_CFLAGS = -Wall
obj-m = hello.o

KDIR = /lib/modules/`uname -r`/build

all:
	make -C $(KDIR) M=`pwd` modules

clean:
>>>>>>> Stashed changes
	make -C $(KDIR) M=`pwd` clean