#
#	FreeRTOS portable layer for RaspberryPi
#
OBJECTS += $(BUILD_DIR)FreeRTOS/portable/GCC/RaspberryPi/port.o
OBJECTS += $(BUILD_DIR)FreeRTOS/portable/GCC/RaspberryPi/portisr.o

#
#	FreeRTOS Core
#
OBJECTS += $(BUILD_DIR)FreeRTOS/croutine.o
OBJECTS += $(BUILD_DIR)FreeRTOS/list.o
OBJECTS += $(BUILD_DIR)FreeRTOS/queue.o
OBJECTS += $(BUILD_DIR)FreeRTOS/tasks.o

#
#	Selected HEAP implementation for FreeRTOS.
#
OBJECTS += $(BUILD_DIR)FreeRTOS/portable/MemMang/heap_4.o
