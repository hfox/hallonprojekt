#include "uart.h"

/* Definition of variables from header file. */
xSemaphoreHandle ReadSemaphore;
xSemaphoreHandle WriteSemaphore;

int SetupUART(void)
{
	/* Mutexes have priority inheritance, semaphores do not. Free choice. */
	vSemaphoreCreateBinary(ReadSemaphore);
	vSemaphoreCreateBinary(WriteSemaphore);
	
	/* TODO: Set up registers and stuff. */
	return 0;
}

/* These functions should be inlined where possible, to give more predictable
 * stack usage to functions like putchar() etc. Therefore they MUST be put in
 * the header file! TODO */

/* Is it possible to remove the temp variable? */

/* TODO: The while loops are basically a busy-wait. This means that they will
 * not yield if they are blocking. Set up some interrupt or similar?
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
int ReadUART(void)
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

/* Non-blocking version */
/*
	if(xSemaphoreTake(WriteSemaphore,0)||IOWord(UART0_FR)&FR_RXFE)
		return EOF;
	else
		return (IOWord(UART0_DR)&DR_DATA);
*/
