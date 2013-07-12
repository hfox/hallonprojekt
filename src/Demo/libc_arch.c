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

/* To ensure arrno is not a macro, but instead an external variable. */
#include <errno.h>
#undef errno
extern int errno;

/*_exit*/

/*close*/
/* Close a stream. Stream-less implementation. */
int _close(int file)
{
	return -1;
}

/*environ*/
/*execve*/
/*fork*/

/*fstat*/
/* Status of open file. By this implementation, all files are said to be
 * character specials. */
int _fstat(int file, struct stat *st) {
	st->st_mode = S_IFCHR;
	return 0;
}

/*getpid*/

/*isatty*/
/* Returns 1 if file descriptor is a terminal. As we cannot open files, any
 * open file is a terminal. */
int _isatty (int file)
{
	return 1;
}

/*kill*/
/*link*/

/*lseek*/
/* Seek within a file. Cheap-o implementation. */
int _lseek(int file, int ptr, int dir){
	return 0;
}

/*open*/

/*read*/
/* Read characters from a file. In this case, only the debug console. */
/*
int _read (int fd, char* buf, int size)
{
	int c;
	int read=0;
	const char* end=buf+size;
	
	while(read<size){
		c=ReadUART();
		if(c==EOF) break;
		buf[read]=c;
		read++;
	}
	
	return read;
}
*/
/*int _read (int fd, char* buf, int size)
{
	int c;
	int read=0;
	const char* end=buf+size;
	
	while(read<size){
		c=ReadUART();
		if(c==EOF) break;
		buf[read]=c;
		read++;
	}
	
	return read;
}*/
int _read (int fd, char* buf, int size)
{
	if(size<=0) return 0;

	*buf=ReadUART();
	return 1;
}


/*sbrk*/
/* Increase program data space. */
/* TODO: Not thread safe! Can it even be smacked into submission?
 * http://lifecs.likai.org/2010/02/sbrk-is-not-thread-safe.html
 * Could one possibly use malloc from inside this function? */
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
	int written=0;
	while(written<size){
		WriteUART(buf[written]);
		written++;
	}
	return written;
}
