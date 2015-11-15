all: kernel modules

clean:
	+ make -C src/kernel clean
	+ make -C src/modules clean
	rm output/lfoskrnl.lfx
	rm output/init

kernel:
	+ make -C src/kernel

modules:
	+ make -C src/modules

test: kernel modules
	qemu-system-i386 -m 256 -kernel output/lfoskrnl.lfx -initrd output/init

debug: kernel modules
	setsid qemu-system-i386 -s -S -m 256 -kernel output/lfoskrnl.lfx -initrd output/init &
	gdb --tui --eval-command="target remote localhost:1234" output/lfoskrnl.lfx

.PHONY: clean all
