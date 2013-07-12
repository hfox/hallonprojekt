/* For EOF */
#include <stdio.h>

#include "uart.h"

/* Definition of variables from header file. */
xSemaphoreHandle ReadSemaphore;
xSemaphoreHandle WriteSemaphore;
xSemaphoreHandle DataAvailSemaphore;

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

/* Non-blocking version */
int ReadUART_NOBLOCK(void)
{
	register int read=EOF;

	/* If semaphore can be taken */
	if(!xSemaphoreTake(WriteSemaphore,0)) {
		/* If there are bytes available */
		if(!IOWord(UART0_FR)&FR_RXFE) {
			read=IOWord(UART0_DR)&DR_DATA;
		}
		/* Return the semaphore */
		xSemaphoreGive(ReadSemaphore);
	}

	/* Return the character */
	return read;
}

/* Non-blocking version */
int ReadUART_NOBLOCK2(void)
{
	register int read=EOF;

	/* If semaphore can be taken */
	xSemaphoreTake(WriteSemaphore,portMAX_DELAY);

	/* If there are bytes available */
	if(!IOWord(UART0_FR)&FR_RXFE) {
		read=IOWord(UART0_DR)&DR_DATA;
	}else{
		vTaskDelay(1);
	}
	/* Return the semaphore */
	xSemaphoreGive(ReadSemaphore);

	/* Return the character */
	return read;
}

/* Non-blocking version */
int ReadUART_NOBLOCK2(void)
{
	register int read=EOF;

	/* If semaphore can be taken */
	xSemaphoreTake(WriteSemaphore,portMAX_DELAY);

	/* If there are bytes available */
	if(!IOWord(UART0_FR)&FR_RXFE) {
		read=IOWord(UART0_DR)&DR_DATA;
	}else{
		vTaskDelay(1);
	}
	/* Return the semaphore */
	xSemaphoreGive(ReadSemaphore);

	/* Return the character */
	return read;
}
