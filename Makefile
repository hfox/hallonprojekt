#
#	Makefile for FreeRTOS demo on Raspberry Pi
#
BASE=$(shell pwd)/
BUILD_DIR=$(shell pwd)/build/

MODULE_NAME="RaspberryPi BSP"

TARGETS=kernel.img kernel.list kernel.syms kernel.elf
LINKER_SCRIPT=raspberrypi.ld

-include .dbuild/dbuild.mk


all: kernel.list kernel.img kernel.syms
	@$(SIZE) kernel.elf

kernel.img: kernel.elf
	$(Q)$(PRETTY) IMAGE $(MODULE_NAME) $@
	$(Q)$(OBJCOPY) kernel.elf -O binary $@

kernel.list: kernel.elf
	$(Q)$(PRETTY) LIST $(MODULE_NAME) $@
	$(Q)$(OBJDUMP) -D -S  kernel.elf > $@

kernel.syms: kernel.elf
	$(Q)$(PRETTY) SYMS $(MODULE_NAME) $@
	$(Q)$(OBJDUMP) -t kernel.elf > $@

kernel.elf: LDFLAGS += -L "/usr/local/lib/gcc/arm-none-eabi/4.7.3" -lgcc
kernel.elf: LDFLAGS += -L "/usr/local/arm-none-eabi/lib" -lc
kernel.elf: $(OBJECTS)
	$(Q)$(LD) $(OBJECTS) -Map kernel.map -o $@ -T $(LINKER_SCRIPT) $(LDFLAGS)

distclean: clean
	rm -rf kernel.map build