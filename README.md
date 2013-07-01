# Hallonprojekt

This is a rough branch of the FreeRTOS port for Raspberry Pi. Some drivers have
been added, and some cleaning of make files have been made. Also the Demo has
been changed.

## Building

(These need to be more in detail)

Download an appropriate toolchain from https://launchpad.net/gcc-arm-embedded/+download
and extract in /usr/local. Run make and you will get a file named kernel.img.
If you have a RPi bootable SD card, it is easiest just to replace the existing
kernel.img with the new one.

## Using the Demo

All I/O is currently done on the UART. If everything works correctly you will
have all characters written to the UART echoed, and the ACT led will blink with
a frequency of ~1 Hz.

----

The original README has been retained below.

# FreeRTOS Ported to Raspberry Pi

This provides a very basic port of FreeRTOS to Raspberry pi.

## Howto Build

Type make! -- If you get an error then:

    $ cd .dbuild/pretty
    $ chmod +x *.py

Currently the makefile expect an arm-none-eabi- toolchain in the path. Either export the path to yours or
modify the TOOLCHAIN variable in dbuild.config.mk file.

You may also need to modify the library locations in the Makefile:

kernel.elf: LDFLAGS += -L"c:/yagarto/lib/gcc/arm-none-eabi/4.7.1/" -lgcc
kernel.elf: LDFLAGS += -L"c:/yagarto/arm-none-eabi/lib/" -lc

The build system also expects find your python interpreter by using /usr/bin/env python,
if this doesn't work you will get problems.

To resolve this, modify the #! lines in the .dbuild/pretty/*.py files.

Hope this helps.

I'm currently porting my BitThunder project to the Pi, which is a OS based on FreeRTOS
but with a comprehensive driver model, and file-systems etc.

http://github.com/jameswalmsley/bitthunder/

James

