#Set correct architecture
CFLAGS += -march=armv6z -g

#Include filed for FreeRTOS
CFLAGS += -I $(BASE)FreeRTOS/Source/portable/GCC/RaspberryPi/
CFLAGS += -I $(BASE)FreeRTOS/Source/include/

#Include files for demo drivers
CFLAGS += -I $(BASE)Demo/Drivers/

TOOLCHAIN=arm-none-eabi-
