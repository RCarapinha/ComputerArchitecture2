#include <detpic32.h>

void delay(unsigned int);
void putc(unsigned char);
void puts(unsigned char*);
void configUart(unsigned int, char, unsigned int);

int main(void){
	configUart(115200, 'N', 1);
    TRISBbit.TRISB6 = 0;
	while(1){
        LATBbits.LATB6=1;
		puts("12345");
		LATBbits.LATB6=0;
	}
}

void configUart(unsigned int baud, char parity, unsigned int Stopbits){
	if(baud<600 || baud > 115200){
		baud = 115200;
	}
	if(parity!='N' && parity!='E' && parity!='O'){
		parity = 'N';
	}
    if(Stopbits!=1 && Stopbits!=2){
		Stopbits = 1;
	}

	U1BRG = ((20000000 + 8*baud)/ (16*baud))-1;
	U1MODEbits.BRGH = 0;

	if(parity=='N'){
		U1MODEbits.PDSEL = 00;
	}else if(parity=='E'){
		U1MODEbits.PDSEL = 01;
	}else if(parity=='O'){
		U1MODEbits.PDSEL = 10;
	}
	/*
	PDSEL<1:0>: Parity and Data Selection bits
	11 = 9-bit data, no parity
	10 = 8-bit data, odd parity
	01 = 8-bit data, even parity
	00 = 8-bit data, no parity
	*/

	U1MODEbits.STSEL = (--Stopbits);

	/*
	STSEL: Stop Selection bit
	1 = 2 Stopbits
	0 = 1 Stopbit
	*/

	U1STAbits.UTXEN = 1;
	U1STAbits.URXEN = 1;

	U1MODEbits.ON = 1;
}


void putc(unsigned char byte2send){
	while(U1STAbits.UTXBF);

	U1TXREG = byte2send;
}

void delay(unsigned int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);
    }
}

void puts(unsigned char* string){
	int i = 0;
	while(string[i]!='\0'){
		putc(string[i++]);
	}
}
