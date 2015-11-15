#include <lf_os.h>
#include <string.h>
#include <scheduler.h>

#include "../../modules/module.h"

void testTask1() {
    while(true) {
        for(char c = 'A'; c <= 'Z'; c++) {
            *((char*)0xB8000) = c;
        }
    }
}

void kernelMain(char *ptrInitrd, int initrdLength)
{
    uint32_t* magic_pointer = (uint32_t*)ptrInitrd;

    while((*magic_pointer) != 0x1F0510AD && magic_pointer < (uint32_t*)(ptrInitrd + initrdLength)) {
        magic_pointer += sizeof(uint32_t);
    }

    struct module_collection* modules = (struct module_collection*)magic_pointer;

    if(modules->version_major != 0 || modules->version_minor != 1) {
        archPanic("Invalid module collection version");
    }

    if(modules->checksum != -(modules->magic + modules->version_major + modules->version_minor + modules->num_modules)) {
        archPanic("Module collection checksum is invalid");
    }

    // everything is right, copy it to the right place
    memcpy((char*)0x8000000, (char*)magic_pointer, initrdLength);

    for(int step = 1; step < 12; step++) {
        for(int i = 0; i < modules->num_modules; i++) {
            if(modules->modules[i].type == step) {
                modules->modules[i].init();
            }
        }
    }

    Scheduler::initialize();
    Scheduler::addTask(testTask1);

    asm("sti");

    while(1);
}
