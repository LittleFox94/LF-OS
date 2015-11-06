[bits 32]

extern archMain
global _start

section multiboot
align 4
	FLAGS		equ 0x0
	MAGIC		equ 0x1BADB002      	; Magicnumber - Erkennungsmerkmal für GRUB
	CHECKSUM	equ -(MAGIC + FLAGS)	; Checksum
	MultiBootHeader:  
		dd MAGIC		; Magic number
		dd FLAGS		; Flags
		dd CHECKSUM		; Checksum


section .text

_start:
	mov esp, 0xEFFFFF 	; Stack an 4MB
	push ebx			; push multiboot-structure to stack -> argument for archMain()
	call archMain
