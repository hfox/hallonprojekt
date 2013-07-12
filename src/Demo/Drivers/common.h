/* Some common definitions of helper macros and addresses */

#ifndef _COMMON_H_
#define _COMMON_H_

#define IOBASE		0x20000000


/* All pointers are volatile to avoid optimization problems */

/**
 * @brief Read and write words (32-bit integers)
 * @parameter Address to read/write
 */
#define IOWord(_ADDR)	(*(volatile int*)(_ADDR))

/**
 * @brief Read and write short integers (16-bit)
 * @parameter Address to read/write
 */
#define IOShort(_ADDR)	(*(volatile short*)(_ADDR))

/**
 * @brief Read and write characters (8-bit integers)
 * @parameter Address to read/write
 */
#define IOChar(_ADDR)	(*(volatile char*)(_ADDR))

/**
 * @brief Address specific bits
 * @parameter Bit to arrdess (0 is LSB)
 */
#define BIT(_N)		(1<<(_N))

/**
 * @brief Set bits in address (32-bit)
 * @parameter Address
 * @parameter Mask for bits to set
 **/
#define SetBit(_ADDR,_BIT) do{IOWord(_ADDR)|=(_BIT);}while(0)

/**
 * @brief Clear bits in address (32-bit)
 * @parameter Address
 * @parameter Mask for bits to clear
 **/
#define ClearBit(_ADDR,_BIT) do{IOWord(_ADDR)&=~(_BIT);}while(0)

#endif
