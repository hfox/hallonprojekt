.PHONY: demo

all: demo


demo: FreeRTOS.a Drivers.a
	make -C Demo
	cp Demo/demo.img Demo/demo.elf .

FreeRTOS.a:
	make -C FreeRTOS
	cp FreeRTOS/FreeRTOS.a .

Drivers.a:
	make -C Drivers
	cp Drivers/Drivers.a .

clean:
	-make -C Demo clean
	-make -C Drivers clean
	-make -C FreeRTOS clean
	rm -rf FreeRTOS.a Drivers.a demo.* build
