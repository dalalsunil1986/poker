#include <stdint.h>
#define UINT64PTR(x) ((uint64_t *) (x))
#define BYTEPTR(x) ((uint8_t *) (x))
#define UART_BASE 0x10000000
#define REG32(x) ((unsigned int *) (x))
#define PLIC_BASE 0x0c000000

void putc(char c) {

	*BYTEPTR(UART_BASE) = c;

}

void puts(const char *string) {
	
	
	while(*string != '\0') {
		putc(*string);
	 	++string;
	}
}



char getc() {
	char c = *BYTEPTR(UART_BASE);
	while(*BYTEPTR(UART_BASE + 5) & 1 == 0);
	switch(c) {
		case 10:
			return '\n';
		case 13:
			return '\n';
		default:
			return c;
	}

}
int test(long mcause) {
	if(mcause < 0) {
		
		putc(*BYTEPTR(UART_BASE));

		unsigned int vector = *((unsigned int *)0x0C200004);
		*((unsigned int *)0x0C200004) = vector;

	} else {
		puts("exception\n");
		if(mcause == 11) {
			puts("clearing msip and msie");

		}
		putc('0' + mcause);

	}

}

void set_color() {
	puts("\x1b[36m");
}



void main() {	
	//enable IER
	*BYTEPTR(UART_BASE + 1) = (1 << 0);
	*BYTEPTR(UART_BASE + 2) = (1 << 0);
	//enable
	unsigned int *enable = (unsigned int *) 0x0C002000;
	*enable = (1 << 10);
	//priority
	unsigned int *priority = (unsigned int *) (0x0C000000 + 4 * 10);
	*priority = 7;
	unsigned int *threshold = (unsigned int *) 0x0C200000;
	*threshold = 6;
	set_color();
	puts("trap handler installed\n");
	puts("Platform Local Interrupt controller installed\n");
	puts("UART enabled\n");
	puts("Hello OSDEV!\n");

	while(1) {
		//putc(getc());
	}


}
