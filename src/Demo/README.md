# Demo

Skall ha två processer; en för att blinka ACT-LED och en för echo på konsolen.

libc-arch.c är den implementationsspecifika delen av newlib. Borde brytas ut.

Kompilerar inte just nu. Behöver avbrottsdriven UART för att ge processer
tid då man väntar på I/O.
