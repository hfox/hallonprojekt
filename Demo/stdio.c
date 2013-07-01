#include "stdio.h"

#include "uart.h"

/* Functions declared as inline are only inlined in this translation unit.
 * Therefore, the stack usage elsewhere is predictable, and stack usage
 * locally is minimal.
 */

inline int putchar(int ch)
{
	return WriteUART(ch);
}

inline int getchar()
{
	return ReadUART();
}

int puts(const char* s)
{
	while(*s)
		if (putchar(*s++)==EOF) return EOF;
	return 0;
}
