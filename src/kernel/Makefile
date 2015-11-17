SRCS = $(shell find -name '*.cpp' -o -name '*.S' -or -name '*.c') # alle *.cpp, *.c und *.S Dateien suchen
OBJS = $(addsuffix .o,$(basename $(SRCS)))

AS = nasm
CC = colorgcc
CPP = colorgcc
LD = ld

ASFLAGS = -f elf -F dwarf
CFLAGS = -m32 -Wall -g -fstack-protector-strong -nostdinc -I include -Wno-write-strings
CPPFLAGS = -m32 -g -I include -Wno-write-strings -nostdlib -fno-use-cxa-atexit -fno-builtin -fno-rtti -fno-exceptions -fstack-protector-strong -c -mfpmath=387 -std=gnu++11
LDFLAGS = -melf_i386 -Tlinker.ld

lfoskrnl.lfx: $(OBJS)
	$(LD) $(LDFLAGS) -o ../../output/$@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c -o $@ $^

%.o: %.S
	$(AS) $(ASFLAGS) -o $@ $^

clean:
	rm $(OBJS)

.PHONY: clean
