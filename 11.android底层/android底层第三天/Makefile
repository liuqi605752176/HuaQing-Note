KERNELDIR  :=/home/linux/fspad_733/lichee/linux-3.4

test:
	make   ARCH=arm  CROSS_COMPILE=arm-linux-gnueabi-  -C  $(KERNELDIR)  M=$(shell  pwd)  modules  

clean:
	make  ARCH=arm   CROSS_COMPILE=arm-linux-gnueabi- -C  $(KERNELDIR)  M=$(shell  pwd)  clean



obj-m  +=led.o
