#
#	Makefile for FreeRTOS archive on Raspberry Pi
#
BASE=$(shell pwd)/../
BUILD_DIR=$(shell pwd)/build/

MODULE_NAME="Demo"

TARGETS=demo.img demo.list demo.syms demo.elf
LINKER_SCRIPT=raspberrypi.ld

-include ../.dbuild/dbuild.mk

all: demo.list demo.img demo.syms
	@$(SIZE) demo.elf

.PHONY: demo
demo: demo.img demo.list demo.syms
demo.img: demo.elf
	$(Q)$(PRETTY) IMAGE $(MODULE_NAME) $@
	$(Q)$(OBJCOPY) demo.elf -O binary $@
                                            
demo.list: demo.elf                                         
	$(Q)$(PRETTY) LIST $(MODULE_NAME) $@
	$(Q)$(OBJDUMP) -D -S  demo.elf > $@

demo.syms: demo.elf
	$(Q)$(PRETTY) SYMS $(MODULE_NAME) $@
	$(Q)$(OBJDUMP) -t demo.elf > $@

demo.elf: LDFLAGS += -L "/usr/local/lib/gcc/arm-none-eabi/4.7.3" -lgcc
demo.elf: LDFLAGS += -L "/usr/local/arm-none-eabi/lib" -lc
demo.elf: LIBS += "../Drivers.a" "../FreeRTOS.a"
demo.elf: $(OBJECTS)
	$(Q)$(LD) $(OBJECTS) $(LIBS) -Map demo.map -o $@ -T $(LINKER_SCRIPT) $(LDFLAGS)

distclean: clean
	rm -rf demo.map build
