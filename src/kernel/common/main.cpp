#include <lf_os.h>
#include <string.h>
#include <scheduler.h>
#include <syscalls.h>

#include "../../modules/module.h"

void render(char* text, int pos) {
    uint16_t* base_vga = (uint16_t*)(0xB8000 + (10 * 80 * 2));
    pos = Scheduler::getCurrentPid() - 3;

    char* local_text = text + pos;

    while(true) {
        while(*local_text) {
            base_vga[pos] = *local_text | (0x07 << 8);
            local_text++;

            asm("int $147"::"a"(make_syscall_code(SyscallGroup::ProcessManagement, Syscalls::Sleep)), "b"(250));
        }

        local_text = text;
    }
}

void testTask1() {
    char* text = "This is an example text rendered by a fork for each character       * * *       ";

    for(int i = 0; i < strlen(text); i++) {
        pid_t fork_pid;
        asm("int $147":"=b"(fork_pid):"a"(make_syscall_code(SyscallGroup::ProcessManagement, Syscalls::Fork)));

        if(fork_pid == 0) {
            render(text, i);
        }
    }

    while(true);
}

void testTask2() {
    while(true) {
        char* chars = "-/|\\-/|\\";
        while(*chars) {
            *((char*)0xB8000) = *chars;
            chars++;

            asm("int $147"::"a"(make_syscall_code(SyscallGroup::ProcessManagement, Syscalls::Sleep)), "b"(100));
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
    Scheduler::addTask(testTask2);

    asm("sti");

    while(1);
}
