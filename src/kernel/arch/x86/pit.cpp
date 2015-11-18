#include "include/pit.h"
#include "include/io.h"

void init_pit() {
    int freq = 1000;
    
    int counter = 1193182 / freq;
    outb(0x43, 0x34);
    outb(0x40,counter & 0xFF);
    outb(0x40,counter >> 8);
}
