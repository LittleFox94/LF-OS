SRCS = $(shell find -name '*.cpp' -o -name '*.S' -or -name '*.c') # alle *.cpp, *.c und *.S Dateien suchen
OBJS = $(addsuffix .o,$(basename $(SRCS)))

AS = nasm
CC = colorgcc
CPP = colorgcc
LD = ld

ASFLAGS = -f elf
CFLAGS = -m32 -Wall -g -fno-stack-protector -nostdinc -I include -Wno-write-strings
CPPFLAGS = -m32 -I include -Wno-write-strings -nostdlib -fno-use-cxa-atexit -fno-builtin -fno-rtti -fno-exceptions -c -mfpmath=387
LDFLAGS = -melf_i386 -Tlinker.ld

init: init.elf
	objcopy -O binary $^ ../../output/$@

init.elf: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ $^

%.o: %.S
	$(AS) $(ASFLAGS) -o $@ $^

clean:
	rm $(OBJS) init.elf

.PHONY: clean
