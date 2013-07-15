#
#	Startup and platform initialisation code.
#
#OBJECTS += $(BUILD_DIR)Drivers/startup.o

#
#	Interrupt Manager & GPIO Drivers
#
OBJECTS += $(BUILD_DIR)Drivers/interrupts.o
OBJECTS += $(BUILD_DIR)Drivers/gpio.o
OBJECTS += $(BUILD_DIR)Drivers/uart.o
