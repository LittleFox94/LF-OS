void module_init_bootscreen() {
    unsigned short *vga = (unsigned short*)0xB8000;

    for(int i = 0; i < 80*25; i++) {
        vga[i] = ' ' | (0x00 << 8);
    }

    char* hello_message = "   LF OS - the 4th attempt\n"
                          "  =========================\n"
                          "Release built on " __DATE__ " at " __TIME__ "\n\n"
                          "Booting ...";

    int x = 0, y = 0;
    char c;
    while((c = *(hello_message++))) {
        if(c == '\n') {
            x = 0;
            y++;
            continue;
        }

        vga[(y * 80) + x] = c | (0x0e << 8);
        x++;
    }
}
