obj-m += Test.o


all:
	make --directory /lib/modules/$(shell uname --kernel-release)/build M=$(PWD) modules

clean:
	make --directory /lib/modules/$(shell uname --kernel-release)/build M=$(PWD) clean


