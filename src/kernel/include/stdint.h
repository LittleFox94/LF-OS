#ifndef _STDINT_H_INCLUDED
#define _STDINT_H_INCLUDED

typedef unsigned char		uint8_t;
typedef		 	 char		int8_t;

typedef unsigned short		uint16_t;
typedef		 	 short		int16_t;

typedef unsigned int		uint32_t;
typedef 	 	 int		int32_t;

typedef unsigned long long	uint64_t;
typedef 	 	 long long	int64_t;

typedef	unsigned int	 	size_t;

#define PACKED __attribute__((packed))

#ifdef _cplusplus
#define NULL 0
#else
#define NULL ((void*)0)
#endif
#define null NULL

#endif
