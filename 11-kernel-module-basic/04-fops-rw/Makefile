EXTRA_CFLAGS = -Wall
obj-m = hello.o

KDIR := /lib/modules/$(shell uname -r)/build
CC := gcc

KBUILD_CFLAGS := $(filter-out -ftrivial-auto-var-init=zero, $(KBUILD_CFLAGS))

all:
	$(MAKE) -C $(KDIR) M=$(shell pwd) modules
	$(CC) -o app test_app.c

clean:
	$(MAKE) -C $(KDIR) M=$(shell pwd) clean
	rm -f app
