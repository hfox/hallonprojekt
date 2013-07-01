/* Some common definitions of helper macros and addresses */

#ifndef _COMMON_H_
#define _COMMON_H_

#define IOBASE		0x20000000


/* All pointers are volatile as to avoid optimization problems */

/**
 * @brief Read and write words (32-bit integers)
 */
#define IOWord(ADDR)	(*(volatile int*)(ADDR))

/**
 * @brief Read and write short integers (16-bit)
 */
#define IOShort(ADDR)	(*(volatile short*)(ADDR))

/**
 * @brief Read and write characters (8-bit integers)
 */
#define IOChar(ADDR)	(*(volatile char*)(ADDR))


#define BIT(_N)		(1<<_N)

#endif
