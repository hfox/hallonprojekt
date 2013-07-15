#include <FreeRTOS.h>
#include <task.h>

#include "interrupts.h"
#include "gpio.h"
#include "uart.h"

#include <stdio.h>

void echo_task(void *pParam) {
	char c;

	while(1) {
		c=getchar();
		putchar(c);
	}
}

void led_task(void *pParam)
{
	/* LED initially off */
	int i = 0;
	while(1) {
		/* Toggle LED status */
		i^=1;
		/* Write LED */
		SetGpio(16, i);
		/* Delay */
		vTaskDelay(1000);
		puts("LED status change\r");
	}
}


void main(void) {
	/* ??? */
	DisableInterrupts();
	InitInterruptController();

	/* Set LED pin to output */
	SetGpioFunction(16, 1);

	/* Setup UART */
	SetupUART();

	puts("Test - Character echo\r");

	/* Code entry point, task handle, stack word depth, arguments, priority, handle pointer */
	xTaskCreate(echo_task, "ECHO", 128, NULL, 0, NULL);
	xTaskCreate(led_task, "LED", 128, NULL, 1, NULL);

	vTaskStartScheduler();

	/* We should never reach here, but just in case. */
	puts("Error occured - halting");
	while(1);
}
