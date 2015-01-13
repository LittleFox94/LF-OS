#ifndef _IO_H_INCLUDED
#define _IO_H_INCLUDED

#include <lf_os.h>

static inline void outb(unsigned short port, unsigned char data)
{
	asm volatile ("outb %0, %1" : : "a" (data), "Nd" (port));
}

static inline void outw(unsigned short port, unsigned short data)
{
	asm volatile ("outw %0, %1" : : "a" (data), "Nd" (port));
}

static inline void outl(unsigned short port, unsigned long data)
{
	asm volatile ("outl %0, %1" : : "a" (data), "Nd" (port));
}

static inline unsigned char inb(unsigned short port)
{
	unsigned char val;
	__asm__ __volatile__("inb %1, %0" : "=a" (val) : "Nd" (port));
	return val;
}

static inline unsigned short inw(unsigned short port)
{
	unsigned short val;
	__asm__ __volatile__("inw %1, %0" : "=a" (val) : "Nd" (port));
	return val;
}

static inline unsigned long inl(unsigned short port)
{
	unsigned long val;
	__asm__ __volatile__("inl %1, %0" : "=a" (val) : "Nd" (port));
	return val;
}

#endif
