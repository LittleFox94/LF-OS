global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

global isr32
global isr33
global isr34
global isr35
global isr36
global isr37
global isr38
global isr39
global isr40
global isr41
global isr42
global isr43
global isr44
global isr45
global isr46
global isr47

global isr147

isr0:
    cli
    push dword 0
    push dword 0
    jmp isr_common_stub

;  1: Debug Exception
isr1:
    cli
    push dword 0
    push dword 1
    jmp isr_common_stub

;  2: Non Maskable Interrupt Exception
isr2:
    cli
    push dword 0
    push dword 2
    jmp isr_common_stub

;  3: Int 3 Exception
isr3:
    cli
    push dword 0
    push dword 3
    jmp isr_common_stub

;  4: INTO Exception
isr4:
    cli
    push dword 0
    push dword 4
    jmp isr_common_stub

;  5: Out of Bounds Exception
isr5:
    cli
    push dword 0
    push dword 5
    jmp isr_common_stub

;  6: Invalid Opcode Exception
isr6:
    cli
    push dword 0
    push dword 6
    jmp isr_common_stub

;  7: Coprocessor Not Available Exception
isr7:
    cli
    push dword 0
    push dword 7
    jmp isr_common_stub

;  8: Double Fault Exception (With Error Code!)
isr8:
    cli
    push dword 8
    jmp isr_common_stub

;  9: Coprocessor Segment Overrun Exception
isr9:
    cli
    push dword 0
    push dword 9
    jmp isr_common_stub

; 10: Bad TSS Exception (With Error Code!)
isr10:
    cli
    push dword 10
    jmp isr_common_stub

; 11: Segment Not Present Exception (With Error Code!)
isr11:
    cli
    push dword 11
    jmp isr_common_stub

; 12: Stack Fault Exception (With Error Code!)
isr12:
    cli
    push dword 12
    jmp isr_common_stub

; 13: General Protection Fault Exception (With Error Code!)
isr13:
    cli
    push dword 13
    jmp isr_common_stub

; 14: Page Fault Exception (With Error Code!)
isr14:
    cli
    push dword 14
    jmp isr_common_stub

; 15: Reserved Exception
isr15:
    cli
    push dword 0
    push dword 15
    jmp isr_common_stub

; 16: Floating Point Exception
isr16:
    cli
    push dword 0
    push dword 16
    jmp isr_common_stub

; 17: Alignment Check Exception
isr17:
    cli
    push dword 0
    push dword 17
    jmp isr_common_stub

; 18: Machine Check Exception
isr18:
    cli
    push dword 0
    push dword 18
    jmp isr_common_stub

; 19: Reserved
isr19:
    cli
    push dword 0
    push dword 19
    jmp isr_common_stub

; 20: Reserved
isr20:
    cli
    push dword 0
    push dword 20
    jmp isr_common_stub

	; 21: Reserved
isr21:
    cli
    push dword 0
    push dword 21
    jmp isr_common_stub

; 22: Reserved
isr22:
    cli
    push dword 0
    push dword 22
    jmp isr_common_stub

; 23: Reserved
isr23:
    cli
    push dword 0
    push dword 23
    jmp isr_common_stub

; 24: Reserved
isr24:
    cli
    push dword 0
    push dword 24
    jmp isr_common_stub

; 25: Reserved
isr25:
    cli
    push dword 0
    push dword 25
    jmp isr_common_stub

; 26: Reserved
isr26:
    cli
    push dword 0
    push dword 26
    jmp isr_common_stub

; 27: Reserved
isr27:
    cli
    push dword 0
    push dword 27
    jmp isr_common_stub

; 28: Reserved
isr28:
    cli
    push dword 0
    push dword 28
    jmp isr_common_stub

; 29: Reserved
isr29:
    cli
    push dword 0
    push dword 29
    jmp isr_common_stub

; 30: Reserved
isr30:
    cli
    push dword 0
    push dword 30
    jmp isr_common_stub

; 31: Reserved
isr31:
    cli
    push dword 0
    push dword 31
    jmp isr_common_stub
	
; IRQ0
isr32:
    cli
    push dword 0
    push dword 32
    jmp isr_common_stub
	
; IRQ1
isr33:
    cli
    push dword 0
    push dword 33
    jmp isr_common_stub
	
; IRQ2
isr34:
    cli
    push dword 0
    push dword 34
    jmp isr_common_stub
	
; IRQ3
isr35:
    cli
    push dword 0
    push dword 35
    jmp isr_common_stub
	
; IRQ4
isr36:
    cli
    push dword 0
    push dword 36
    jmp isr_common_stub
	
; IRQ5
isr37:
    cli
    push dword 0
    push dword 37
    jmp isr_common_stub
	
; IRQ6
isr38:
    cli
    push dword 0
    push dword 38
    jmp isr_common_stub
	
; IRQ7
isr39:
    cli
    push dword 0
    push dword 39
    jmp isr_common_stub
	
; IRQ8
isr40:
    cli
    push dword 0
    push dword 40
    jmp isr_common_stub
	
; IRQ9
isr41:
    cli
    push dword 0
    push dword 41
    jmp isr_common_stub
	
; IRQ10
isr42:
    cli
    push dword 0
    push dword 42
    jmp isr_common_stub
	
; IRQ11
isr43:
    cli
    push dword 0
    push dword 43
    jmp isr_common_stub
	
; IRQ12
isr44:
    cli
    push dword 0
    push dword 44
    jmp isr_common_stub
	
; IRQ13
isr45:
    cli
    push dword 0
    push dword 45
    jmp isr_common_stub
	
; IRQ14
isr46:
    cli
    push dword 0
    push dword 46
    jmp isr_common_stub
	
; IRQ15
isr47:
    cli
    push dword 0
    push dword 47
    jmp isr_common_stub
	
; nextgen LF ABI
isr147:
    cli
    push 0
    push 48
    jmp isr_common_stub
	
extern interrupt_handler

isr_common_stub:
    ; CPU-Zustand sichern
    push ebp
    push edi
    push esi
    push edx
    push ecx
    push ebx
    push eax
	;mov eax, cr3
	;push eax
 
	; Kernel-Datensegmente laden
    mov ax, 0x10
    mov ds, ax
    mov es, ax
 
    ; Handler aufrufen
    push esp
    call interrupt_handler
    mov esp, eax
	
	; User-Datensegmente laden
    mov ax, 0x23
    mov ds, ax
    mov es, ax
 
    ; CPU-Zustand wiederherstellen
	;pop eax
	;mov eax, cr3
    pop eax
    pop ebx
    pop ecx
    pop edx
    pop esi
    pop edi
    pop ebp
 
    ; Fehlercode und Interruptnummer vom Stack nehmen
    add esp, 8
 
    ; Ruecksprung zum unterbrochenen Code
    iret
