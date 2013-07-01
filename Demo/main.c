#include <FreeRTOS.h>
#include <task.h>

#include "Drivers/interrupts.h"
#include "Drivers/gpio.h"

#include "stdio.h"

void echo_task(void *pParam) {
	char c;

	while(1) {
		c=getchar();
		putchar(c);
	}
}

void led_task(void *pParam) {

	int i = 0;
	while(1) {
		i^=1;
		SetGpio(16, i);
		vTaskDelay(500);
	}
}


void main(void) {
	DisableInterrupts();
	InitInterruptController();

	SetGpioFunction(16, 1);

	SetupUART();

	puts("Test - Charcter echo\n");

	/* Code entry point, task handle, stack word depth, arguments, priority, handle pointer */
	xTaskCreate(echo_task, "ECHO", 128, NULL, 0, NULL);
	xTaskCreate(led_task, "LED", 128, NULL, 1, NULL);

	vTaskStartScheduler();

	/* We should never reach here, but just in case. */
	puts("Error occured - halting\n");
	while(1);
}
