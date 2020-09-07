obj-m += solution8.o
MOD_NAME = solution8.ko

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

load: all
	sudo insmod $(MOD_NAME)
	sudo dmesg -c

unload:
	sudo rmmod $(MOD_NAME)
	sudo dmesg -c
