#ifndef _X86_H_INCLUDED
#define _X86_H_INCLUDED

#include <lf_os.h>
#include "cpu.h"
#include "io.h"

extern uint32_t tss[32];

/** This function doesn't depend on any other function
  * so it can be called anytime
  */
void archPanic(char *text);

// init functions
void init_gdt();
void init_idt();
void init_irqs();

// unsorted functions
struct cpu_state *irq_handler(struct cpu_state *cpu);
struct cpu_state *lf_abi_handler(struct cpu_state *cpu);

// let's crash the computer :D
void crash(char *text);

#endif
