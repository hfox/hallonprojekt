Kompilera och länka mot FreeRTOS för Raspberry Pi tillgängligt på
https://github.com/jameswalmsley/RaspberryPi-FreeRTOS

libc-arch.c är den implementationsspecifika delen av newlib. Många av filerna,
till exempel de i Drivers, går att återanvända och borde därmed brytas ut.

Kompilerar inte just nu. Behöver även avbrottsdriven UART för att ge processer
tid då man väntar på I/O.
