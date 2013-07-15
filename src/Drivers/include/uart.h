/**
 * @file uart.h
 * @brief Driver for the serial console.
 *
 * Functions for setting up and reding/writing the UART.
 */

#ifndef _UART_H_
#define _UART_H_

/* For semaphores and mutexen */
#include "FreeRTOS.h"
#include "semphr.h"

#include "common.h"

/* TODO: Definition for each register and all of its bits */
/* See datasheet for detailed information of all registers */

#define UART0_BASE		(IOBASE+0x00201000)

#define UART0_DR		(UART0_BASE+0x0)
#define DR_OE			(BIT(11))
#define DR_BE			(BIT(10))
#define DR_PE			(BIT(9))
#define DR_FE			(BIT(8))
#define DR_DATA			(0xFF)

#define UART0_RSRECR	(UART0_BASE+0x04)
#define RSRECR_OE		(BIT(3))
#define RSRECR_BE		(BIT(2))
#define RSRECR_PE		(BIT(1))
#define RSRECR_FE		(BIT(0))

#define UART0_FR		(UART0_BASE+0x18)
#define FR_RI			(BIT(8))
#define FR_TXFE			(BIT(7))
#define FR_RXFF			(BIT(6))
#define FR_TXFF			(BIT(5))
#define FR_RXFE			(BIT(4))
#define FR_BUSY			(BIT(3))
#define FR_DCD			(BIT(2))
#define FR_DSR			(BIT(1))
#define FR_CTS			(BIT(0))

/*#define UART0_		(UART0_BASE+0x)*/
/*#define _			(BIT())*/

#define UART0_LCRH		(UART0_BASE+0x2c)
#define LCRH_SPS		(BIT(7))
#define LCRH_WLEN		(BIT(6)|BIT(5))
#define LCRH_FEN		(BIT(4))
#define LCRH_STP2		(BIT(3))
#define LCRH_EPS		(BIT(2))
#define LCRH_PEN		(BIT(1))
#define LCRH_BRK		(BIT(0))


/**
 * @brief Set up the UART
 * @return 0 if UART correctly set up, else -1
 */
int SetupUART(void);

/**
 * @brief Write a character to the UART
 * @param Character to write
 * @return Character written, or EOF on error
 */
int WriteUART(int);

/**
 * @brief Read a character from the UART
 * @return Character read, or EOF on end of file or error
 */
int ReadUART(void);

#endif /*_UART_H_*/