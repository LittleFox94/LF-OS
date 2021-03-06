[bits 32]

extern archMain
global _start

section multiboot
align 4
	FLAGS		equ 0x0
	MAGIC		equ 0x1BADB002      	; Magicnumber - Erkennungsmerkmal f�r GRUB
	CHECKSUM	equ -(MAGIC + FLAGS)	; Checksum
	MultiBootHeader:  
		dd MAGIC		; Magic number
		dd FLAGS		; Flags
		dd CHECKSUM		; Checksum


section .text

_start:
	mov esp, 0x180000 	; Stack an 1.5MB
	push ebx			; push multiboot-structure to stack -> argument for archMain()
	call archMain
