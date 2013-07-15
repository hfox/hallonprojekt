#Set correct architecture
CFLAGS += -march=armv6z -g -Wall

#Set toolchain prefix
TOOLCHAIN=arm-none-eabi-

#Include files for FreeRTOS
CFLAGS += -I $(BASE)FreeRTOS/include/
CFLAGS += -I $(BASE)FreeRTOS/portable/GCC/RaspberryPi/

#Include files for drivers
CFLAGS += -I $(BASE)Drivers/include/
