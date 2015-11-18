#include <lf_os.h>
#include <scheduler.h>

extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void isr8();
extern "C" void isr9();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();

extern "C" void isr32();
extern "C" void isr33();
extern "C" void isr34();
extern "C" void isr35();
extern "C" void isr36();
extern "C" void isr37();
extern "C" void isr38();
extern "C" void isr39();
extern "C" void isr40();
extern "C" void isr41();
extern "C" void isr42();
extern "C" void isr43();
extern "C" void isr44();
extern "C" void isr45();
extern "C" void isr46();
extern "C" void isr47();

extern "C" void isr147(); // nextgen lf os abi

char *exception_messages[] =
{
    "[ PANIC ] Division By Zero",
    "[ PANIC ] Debug",
    "[ PANIC ] Non Maskable Interrupt",
    "[ PANIC ] Breakpoint",
    "[ PANIC ] Into Detected Overflow",
    "[ PANIC ] Out of Bounds",
    "[ PANIC ] Invalid Opcode",
    "[ PANIC ] No Coprocessor",

    "[ PANIC ] Double Fault",
    "[ PANIC ] Coprocessor Segment Overrun",
    "[ PANIC ] Bad TSS",
    "[ PANIC ] Segment Not Present",
    "[ PANIC ] Stack Fault",
    "[ PANIC ] General Protection Fault",
    "[ PANIC ] Page Fault",
    "[ PANIC ] Unknown Interrupt",

    "[ PANIC ] Coprocessor Fault",
    "[ PANIC ] Alignment Check",
    "[ PANIC ] Machine Check",
    "[ PANIC ] Reserved",
    "[ PANIC ] Reserved",
    "[ PANIC ] Reserved",
    "[ PANIC ] Reserved",
    "[ PANIC ] Reserved",

    "[ PANIC ] Reserved",
    "[ PANIC ] Reserved",
    "[ PANIC ] Reserved",
    "[ PANIC ] Reserved",
    "[ PANIC ] Reserved",
    "[ PANIC ] Reserved",
    "[ PANIC ] Reserved",
    "[ PANIC ] Reserved"
};

struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;

    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void init_idt()
{
    /*             EXCEPTIONS              */
    idt_set_gate(0,(unsigned)isr0,0x08,0x8E);
    idt_set_gate(1,(unsigned)isr1,0x08,0x8E);
    idt_set_gate(2,(unsigned)isr2,0x08,0x8E);
    idt_set_gate(3,(unsigned)isr3,0x08,0x8E);
    idt_set_gate(4,(unsigned)isr4,0x08,0x8E);
    idt_set_gate(5,(unsigned)isr5,0x08,0x8E);
    idt_set_gate(6,(unsigned)isr6,0x08,0x8E);
    idt_set_gate(7,(unsigned)isr7,0x08,0x8E);
    idt_set_gate(8,(unsigned)isr8,0x08,0x8E);
    idt_set_gate(9,(unsigned)isr9,0x08,0x8E);
    idt_set_gate(10,(unsigned)isr10,0x08,0x8E);
    idt_set_gate(11,(unsigned)isr11,0x08,0x8E);
    idt_set_gate(12,(unsigned)isr12,0x08,0x8E);
    idt_set_gate(13,(unsigned)isr13,0x08,0x8E);
    idt_set_gate(14,(unsigned)isr14,0x08,0x8E);
    idt_set_gate(15,(unsigned)isr15,0x08,0x8E);
    idt_set_gate(16,(unsigned)isr16,0x08,0x8E);
    idt_set_gate(17,(unsigned)isr17,0x08,0x8E);
    idt_set_gate(18,(unsigned)isr18,0x08,0x8E);
    idt_set_gate(19,(unsigned)isr19,0x08,0x8E);
    idt_set_gate(20,(unsigned)isr20,0x08,0x8E);
    idt_set_gate(21,(unsigned)isr21,0x08,0x8E);
    idt_set_gate(22,(unsigned)isr22,0x08,0x8E);
    idt_set_gate(23,(unsigned)isr23,0x08,0x8E);
    idt_set_gate(24,(unsigned)isr24,0x08,0x8E);
    idt_set_gate(25,(unsigned)isr25,0x08,0x8E);
    idt_set_gate(26,(unsigned)isr26,0x08,0x8E);
    idt_set_gate(27,(unsigned)isr27,0x08,0x8E);
    idt_set_gate(28,(unsigned)isr28,0x08,0x8E);
    idt_set_gate(29,(unsigned)isr29,0x08,0x8E);
    idt_set_gate(30,(unsigned)isr30,0x08,0x8E);
    idt_set_gate(31,(unsigned)isr31,0x08,0x8E);
    // IRQs
    idt_set_gate(32,(unsigned)isr32,0x08,0x8E);
    idt_set_gate(33,(unsigned)isr33,0x08,0x8E);
    idt_set_gate(34,(unsigned)isr34,0x08,0x8E);
    idt_set_gate(35,(unsigned)isr35,0x08,0x8E);
    idt_set_gate(36,(unsigned)isr36,0x08,0x8E);
    idt_set_gate(37,(unsigned)isr37,0x08,0x8E);
    idt_set_gate(38,(unsigned)isr38,0x08,0x8E);
    idt_set_gate(39,(unsigned)isr39,0x08,0x8E);
    idt_set_gate(40,(unsigned)isr40,0x08,0x8E);
    idt_set_gate(41,(unsigned)isr41,0x08,0x8E);
    idt_set_gate(42,(unsigned)isr42,0x08,0x8E);
    idt_set_gate(43,(unsigned)isr43,0x08,0x8E);
    idt_set_gate(44,(unsigned)isr44,0x08,0x8E);
    idt_set_gate(45,(unsigned)isr45,0x08,0x8E);
    idt_set_gate(46,(unsigned)isr46,0x08,0x8E);
    idt_set_gate(47,(unsigned)isr47,0x08,0x8E);
    // nextgen LF ABI
    idt_set_gate(147,(unsigned)isr147,0x08,0xEE);

    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = (unsigned int)&idt;

    asm volatile("lidt %0" : : "m" (idtp));
}

extern "C" struct cpu_state *interrupt_handler(struct cpu_state *cpu)
{
    if (cpu->intr <= 0x1f)
    {
        archPanic(exception_messages[cpu->intr]);
    }
    else if(cpu->intr <= 0x2f && cpu->intr >= 0x20)
    {
        return irq_handler(cpu);
    }
    else if(cpu->intr == 147) // nextgen LF ABI
    {
        return lf_abi_handler(cpu);
    }
    return cpu;
}

struct cpu_state *irq_handler(struct cpu_state *cpu)
{
    int number = cpu->intr;

    struct cpu_state* new_cpu = HardwareInterrupt(cpu->intr, cpu);

    if (number >= 0x28) {
        outb(0xa0, 0x20);
    }
    outb(0x20, 0x20);

    tss[1] = (uint32_t) (new_cpu + 1);

    return new_cpu;
}

struct cpu_state *lf_abi_handler(struct cpu_state *cpu)
{
    unsigned int *params[3];
    params[0] = &cpu->ebx;
    params[1] = &cpu->ecx;
    params[2] = &cpu->edx;

    bool change_task = false;

    Syscall(cpu->eax, params, 3, &change_task, cpu);

    if(change_task) {
        cpu = Scheduler::nextTask(cpu);
        tss[1] = (uint32_t)(cpu + 1);
    }

    return cpu;
}
