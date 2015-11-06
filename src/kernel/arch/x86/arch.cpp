#include <lf_os.h>
#include "include/x86.h"
#include "include/multiboot.h"

extern "C" void archMain(struct multiboot_info *mbi)
{
    // platform specific setup ...
    init_gdt();
    init_idt();
    init_irqs();

    // getting initrd module
    char *initrd;

    if(mbi->mbs_mods_count == 0)
    {
        archPanic("[ PANIC ] No modules loaded! Please load at least an initial ramdisk (initrd).");
    }

    struct multiboot_module *firstModule = (struct multiboot_module*)mbi->mbs_mods_addr;

    init_pmm();

    pmm_mark_used(mbi);

    for(int i = 0; i < mbi->mbs_mods_count; i++)
    {
        struct multiboot_module * module = (struct multiboot_module *)((uint32_t)mbi->mbs_mods_addr + (sizeof(struct multiboot_module) * i));
        pmm_mark_used((void*)module);

        for(uint64_t addr = module->mod_start; addr < module->mod_end; addr += 0x1000)
        {
            pmm_mark_used((void*)addr);
        }
    }

    struct multiboot_mmap* mmap = (struct multiboot_mmap*)mbi->mbs_mmap_addr;
    struct multiboot_mmap* mmap_end = (struct multiboot_mmap*)((uint32_t) mbi->mbs_mmap_addr + mbi->mbs_mmap_length);

    while (mmap < mmap_end)
    {
        if (mmap->type != 1)
        {
            // Der Speicherbereich ist belegt; entsprechend markieren
            uint32_t addr = mmap->base;
            uint32_t end_addr = addr + mmap->length;

            while (addr < end_addr)
            {
                pmm_mark_used((void*) addr);
                addr += 0x1000;
            }
        }
        mmap++;
    }

    asm("sti");

    // starting the kernel
    kernelMain((char*)firstModule->mod_start, firstModule->mod_end - firstModule->mod_start);

    while(true);

    return;
}

void crash(char *text)
{
    archPanic(text);
}

/** This function doesn't depend on any other function
  * so it can be called anytime
  */
void archPanic(char *text)
{
    uint16_t *videoMem = (uint16_t*)0xB8000;

    for(int i = 0; i < 2000; i++)
    {
        videoMem[i] = 0x0700;
    }

    int i = 0;
    while(*text)
    {
        videoMem[i] = 0x0400 | *text;
        text++;
        i++;
    }

    __asm__("cli;hlt;jmp .");
}
