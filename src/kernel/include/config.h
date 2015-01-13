#ifndef _CONFIG_H_INCLUDED
#define _CONFIG_H_INCLUDED

/* To modify the configuration of LF OS edit the valus in this file.
 * Please leave the other files unchanged.
 *
 * Notes:
 *  - every size value is given in bytes
 *  - if change on value you should take a look through the complete file to
 *    change similiar values
 */

// Define the architecture of the binary here
#define COMPILE_ARCH x86

// Here you can define the maximum amount of memory supported by LF OS.
// This will affect the size of the bitmap used by the physical memory manager.
#define MAXMEM		4294967295ULL /* 4GB */

// Here you can specify the size of the chunks returned by the physical memory
// manager. THis value should be the same as the size of the pages (vmm)!
#define PAGESIZE	4096

// include the header file of the architecture youre compiling for
#include <../arch/x86/include/x86.h>

  //////////////////////////////////////////////////////////////////////////////
 //                   Do not edit things under this line!                    //
//////////////////////////////////////////////////////////////////////////////

// the size of the memory bitmap used by the physical memory manager.
// constant value -> better performance :)
const uint64_t PMMBITMAPSIZE = (uint64_t)((MAXMEM / PAGESIZE) / 64);

#endif
