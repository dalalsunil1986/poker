compile:
	riscv64-unknown-elf-gcc entry.S main.c -o main -T linker.ld -nostdlib -ffreestanding -mcmodel=medany

clean:
	rm -rf main main.o
qemu:
	qemu-system-riscv64 -machine virt -bios none -kernel main -nographic
