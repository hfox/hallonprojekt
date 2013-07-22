/*http://wiki.osdev.org/Porting_Newlib*/

/* This is the glue connecting libc to the operating system and underlying
 * hardware. All of these are designed for a simple system without file
 * support, all I/O is done on the UART. They should be thread safe. */

/* For caddr_t, a safe pointer type. */
#include <sys/types.h>

/* For fstat file modes. */
#include <sys/stat.h>

/* For EOF */
#include <stdio.h>

/* For UART usage */
#include "uart.h"

/* To ensure arrno is not a macro, but instead an external variable. */
#include <errno.h>
#undef errno
extern int errno;

/* To supress warnings about unused parameters */
#define UNUSED(_PARAM) (void)(_PARAM)

/*_exit*/

/*close*/
/* Close a stream. Stream-less implementation. */
int _close(int file)
{
	UNUSED(file);
	return -1;
}

/*environ*/
/*execve*/
/*fork*/

/*fstat*/
/* Status of open file. By this implementation, all files are said to be
 * character specials. */
int _fstat(int file, struct stat *st) {
	UNUSED(file);
	st->st_mode = S_IFCHR;
	return 0;
}

/*getpid*/

/*isatty*/
/* Returns 1 if file descriptor is a terminal. As we cannot open files, any
 * open file is a terminal. */
int _isatty (int file)
{
	UNUSED(file);
	return 1;
}

/*kill*/
/*link*/

/*lseek*/
/* Seek within a file. Cheap-o implementation. */
int _lseek(int file, int ptr, int dir){
	UNUSED(file);
	UNUSED(ptr);
	UNUSED(dir);
	return 0;
}

/*open*/

/*read*/
/* Read characters from a file. In this case, only the debug console.
 * Reading one character at a time should be OK according to the standard;
 * the caller should check the number of bytes read. Most of the time
 * we will just read one character of input anyway.
 */
int _read (int fd, char* buf, int size)
{
	UNUSED(fd);
	if(size<=0) return 0;

	*buf=ReadUART();
	return 1;
}


/*sbrk*/
/* Increase program data space. */
/* NOTE: Due to the nature of this function and newlib, it is only safe to
 * sbrk positive (which means malloc is safe and free is not), and not to
 * assume data is linear, as one could infer from manual pages.
 * http://lifecs.likai.org/2010/02/sbrk-is-not-thread-safe.html
 */
caddr_t _sbrk(int n){
	/* heap_start is defined by the linker, see raspberrypi.ld */
	extern void* heap_start;
	static char *heap_end;
	char *prev_heap_end;

	if (heap_end==0) {
		heap_end=heap_start;
	}
	prev_heap_end=heap_end;
	heap_end+=n;
	
	/* Could check for stack collission here. */
	
	return (caddr_t)prev_heap_end;
}

/*stat*/
/*times*/
/*unlink*/
/*wait*/

/*write*/
/* Write characters to a file. In this case, only debug console. */
int _write (int fd, const char* buf, int size)
{
	UNUSED(fd);
	int written=0;
	while(written<size){
		WriteUART(buf[written]);
		written++;
	}
	return written;
}
