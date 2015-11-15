#ifndef _LF_OS_H_INCLUDED
#define _LF_OS_H_INCLUDED

#include <stdint.h>
#include <config.h>

void init_pmm();

void kernelMain(char *ptrInitrd, int initrdLength);

void Exception(int number, char *errorMsg);
struct cpu_state *HardwareInterrupt(int number, struct cpu_state *cpu);
void Syscall(int number, unsigned int **params, int count);

void pmm_mark_used(void *mem);
void pmm_mark_free(void *mem);
bool pmm_check_free(void *mem);
void *pmm_alloc();
void *pmm_multi_alloc(size_t size);

#endif
