# --- Compilación del driver del kernel ---
obj-m += driver_ACM.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

.PHONY: all driver lib clean

all: driver lib

driver:
	make -C $(KDIR) M=$(PWD) modules

# --- Compilación de biblioteca .a ---
lib: gpio_interface.o
	ar rcs libgpio.a gpio_interface.o

gpio_interface.o: gpio_interface.c gpio_interface.h
	gcc -Wall -O2 -c gpio_interface.c -o gpio_interface.o

clean:
	make -C $(KDIR) M=$(PWD) clean
	rm -f *.o *.a *.ko *.mod.* Module.symvers modules.order
