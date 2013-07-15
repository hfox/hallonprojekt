#
#	Makefile for FreeRTOS archive on Raspberry Pi
#
BASE=$(shell pwd)/../
BUILD_DIR=$(shell pwd)/../build/

MODULE_NAME="Drivers"

TARGETS=Drivers.a

-include ../.dbuild/dbuild.mk

Drivers.a: $(OBJECTS)

distclean: clean
