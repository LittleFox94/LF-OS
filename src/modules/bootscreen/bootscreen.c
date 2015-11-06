void module_init_bootscreen() {
    unsigned short *vga = (unsigned short*)0xB8000;

    for(int i = 0; i < 80*25; i++) {
        vga[i] = 'c' | (0x07 << 8);
    }
}
