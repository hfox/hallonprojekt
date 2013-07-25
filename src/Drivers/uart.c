/* Right now we have an ugly polling UART. TODO. Undef this to try the
 * interrupt driven. Might not work at all. */
#define UART_POLLING

/* For EOF */
#include <stdio.h>

#include "uart.h"

#include "queue.h"

#ifndef UART_POLLING

	#include "gpio.h"
	#include "interrupts.h"

	/* Function to be called when data is received on UART. */
	void RecvUART_interrupt(int nIRQ, void* param);

#endif /* UART_POLLING */

/* Definition of variables from header file. */
xSemaphoreHandle ReadSemaphore;
xSemaphoreHandle WriteSemaphore;

#ifndef UART_POLLING
	xSemaphoreHandle DataAvailSemaphore;
#endif /* UART_POLLING */

/* Interrupt handler for non-polling UART */
#ifndef UART_POLLING
void RecvUART_interrupt(int nIRQ, void* param)
{
	/* Turn off ACT led, so we see if somethings happening */
	/* SetGpio(16,1);*/
	/* Disable interrupt */
	DisableInterrupt(BCM2835_IRQ_ID_GPIO_0);
	/* Wait for byte to be completely received. This will give some jitter
	 * in the running process. More exactly the time it takes to receive
	 * one byte; 1/115200 seconds, which is about 8.68 microseconds. Even
	 * rounding up to 9 µs compensating for interrupt overhead and then some
	 * for good measure, that is not an awful lot. But be aware.
	 * Be very aware.
	 */
	while (IOWord(UART0_FR)&FR_RXFE);
	/* Signal that bytes are available */
	xSemaphoreGive(DataAvailSemaphore);
}
#endif /*UART_POLLING*/

int SetupUART(void)
{
	/* Mutexes have priority inheritance, semaphores do not. Free choice. */
	vSemaphoreCreateBinary(ReadSemaphore);
	vSemaphoreCreateBinary(WriteSemaphore);
#ifndef UART_POLLING
	vSemaphoreCreateBinary(DataAvailSemaphore);
#endif /* UART_POLLING */
	
	/* TODO: Set speed. */
	
	/* Setup speed (default at 115200, we setup at 115200, just to be sure) */
	
	/* Setup bits (8) */
	SetBit(UART0_LCRH,LCRH_WLEN);
	
	/* Setup parity (none) */
	ClearBit(UART0_LCRH,LCRH_PEN);
	
	/* Setup stop bits (1) */
	ClearBit(UART0_LCRH,LCRH_STP2);
	
	/* Setup FIFOs */
	SetBit(UART0_LCRH,LCRH_FEN);
	
#ifndef UART_POLLING
	/* TODO: Setup interrupt vector(s) */
	/* RegisterInterrupt(BCM2835_IRQ_ID_GPIO_0,RecvUART_interrupt,NULL); */
	RegisterInterrupt(49,RecvUART_interrupt,NULL);
	/*RegisterInterrupt(BCM2835_IRQ_ID_GPIO_0,NULL,NULL);*/
	/* TODO: Set interrupt on falling edge of GPIO 15(RX) */
	/* Falling because idle RS232 is held high */
	EnableGpioDetect(15,DETECT_FALLING);
#endif /* UART_POLLING */

	return 0;
}

/* These functions should be inlined where possible, to give more predictable
 * stack usage to functions like putchar() etc. To do that they MUST be put in
 * the header file! TODO */

/* TODO: Set up the FIFO wait for at least read to use interrupts.
 */

int WriteUART(int ch)
{
	/* Wait for WriteSemaphore indefinitely */
	xSemaphoreTake(WriteSemaphore,portMAX_DELAY);
	/* Wait until UART TX FIFO is not full */
	while (IOWord(UART0_FR)&FR_TXFF);
	/* Cast to 8 bits, write, and save */
	ch=(IOWord(UART0_DR)=(char)ch&DR_DATA);
	/* Release the semaphore */
	xSemaphoreGive(WriteSemaphore);
	/* Return the character written */
	return ch;
}

/* Blocking version */
int ReadUART_BLOCK(void)
{
	register int read;
	/* Wait for ReadSemaphore indefinitely */
	xSemaphoreTake(ReadSemaphore,portMAX_DELAY);
	/* Wait until UART RX FIFO is not empty */
	while (IOWord(UART0_FR)&FR_RXFE);
	/* Receive character */
	read=(IOWord(UART0_DR)&DR_DATA);
	/* Return the semaphore */
	xSemaphoreGive(ReadSemaphore);
	/* Return the character */
	return read;
}

/* Blocking version with optional busy wait */
int ReadUART(void)
{
	register int read;
	
	/* Wait for read subsystem to be available */
	xSemaphoreTake(ReadSemaphore,portMAX_DELAY);

#ifdef UART_POLLING

	while(IOWord(UART0_FR)&FR_RXFE) vTaskDelay(10);

#else /* UART_POLLING */

	if(IOWord(UART0_FR)&FR_RXFE) {
		/* If there are no bytes available in FIFO, take the
		 * semaphore, set the data receive interrupt, and wait
		 * for the semaphore to be freed. The FreeRTOS forums
		 * said it was a good idea. */
		xSemaphoreTake(DataAvailSemaphore,portMAX_DELAY);
		/* Start interrupt */
		EnableInterrupt(BCM2835_IRQ_ID_GPIO_0);
		/* Wait for interrupt to free semaphore */
		xSemaphoreTake(DataAvailSemaphore,portMAX_DELAY);

		/* Read byte and give back semaphore */
		read=IOWord(UART0_DR)&DR_DATA;
		xSemaphoreGive(DataAvailSemaphore);
	} else

#endif /* UART_POLLING */

	read=IOWord(UART0_DR)&DR_DATA;
	
	/* Return the read subsystem semaphore */
	xSemaphoreGive(ReadSemaphore);

	/* Return the character */
	return read;
}
