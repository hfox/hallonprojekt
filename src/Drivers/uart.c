/* Time to delay process when polling UART */
#define POLL_DELAY_TIME 10

/* For EOF */
#include <stdio.h>

#include "uart.h"

#include "queue.h"

/* Definition of variables from header file. */
xSemaphoreHandle ReadSemaphore;
xSemaphoreHandle WriteSemaphore;

int SetupUART(void)
{
	/* Mutexes have priority inheritance, semaphores do not. Free choice. */
	vSemaphoreCreateBinary(ReadSemaphore);
	vSemaphoreCreateBinary(WriteSemaphore);
	
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
	
	return 0;
}

/* These functions should be inlined where possible, to give more predictable
 * stack usage to functions like putchar() etc. To do that they MUST be put in
 * the header file! TODO */

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

/* Blocking but yielding version */
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
