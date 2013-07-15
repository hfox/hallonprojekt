#
#	Makefile for FreeRTOS archive on Raspberry Pi
#
BASE=$(shell pwd)/../
BUILD_DIR=$(shell pwd)/../build/

MODULE_NAME="RaspberryPi BSP"

TARGETS=FreeRTOS.a

-include ../.dbuild/dbuild.mk

#FreeRTOS.a:
#	echo $(OBJECTS)
FreeRTOS.a: $(OBJECTS)

distclean: clean
