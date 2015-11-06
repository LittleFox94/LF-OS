[bits 32]

; This file is only the header for the initial module collection.
; It is not supposed to be executed. Every module is it's own program.

extern module_init_bootscreen

global _start

section moduleData
align 4
    MODULE_MAGIC    equ 0x1F0510AD
    VERSION_MAJOR   equ 0
    VERSION_MINOR   equ 1
    NUM_MODULES     equ 1
    CHECKSUM        equ -(MODULE_MAGIC + VERSION_MAJOR + VERSION_MINOR + NUM_MODULES)

    ; this is an "enum"
    MODULE_ARCH_SETUP           equ 2
    MODULE_BUS_DRIVER           equ 4
    MODULE_DEVICE_DRIVER        equ 6
    MODULE_FILESYSTEM_DRIVER    equ 8
    MODULE_PREINIT              equ 10

    ModuleHeader:
        dd MODULE_MAGIC
        dd VERSION_MAJOR
        dd VERSION_MINOR
        dd NUM_MODULES
        dd CHECKSUM

    ModuleEntries:
        __bootscreen:
            dd (MODULE_ARCH_SETUP + 1)
            dd module_init_bootscreen

_start:
    cli
    hlt
    jmp _start
