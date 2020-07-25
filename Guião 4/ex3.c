#include <detpic32.h>

void main(void){
	LATBbits.LATB8 = 0;
	LATBbits.LATB9 = 0;
	LATBbits.LATB10 = 0;
	LATBbits.LATB11 = 0;
	LATBbits.LATB12 = 0;
	LATBbits.LATB13 = 0;
	LATBbits.LATB14 = 0;
	LATBbits.LATB15 = 0;
	
	TRISBbits.TRISB8 = 0;
	TRISBbits.TRISB9 = 0;
	TRISBbits.TRISB10 = 0;
	TRISBbits.TRISB11 = 0;
	TRISBbits.TRISB12 = 0;
	TRISBbits.TRISB13 = 0;
	TRISBbits.TRISB14 = 0;
	TRISBbits.TRISB15 = 0;
	TRISDbits.TRISD5 = 0;
	TRISDbits.TRISD6 = 0;
	
	LATDbits.LATD5 = 0; //Liga Segmento Direita
	LATDbits.LATD6 = 1; //Liga Segmenteo Esquerda
	
	char c;
	while(1){
		printStr("Escreva aqui -> ");
		c = getChar();
		printStr("\n");
		putChar(c);
		printStr("\n");
		switch(c){
			case 'a': 	LATBbits.LATB8 = 1;
						LATBbits.LATB9 = 0;
						LATBbits.LATB10 = 0;
						LATBbits.LATB11 = 0;
						LATBbits.LATB12 = 0;
						LATBbits.LATB13 = 0;
						LATBbits.LATB14 = 0; break;
			
			case 'b':  	LATBbits.LATB8 = 0;
						LATBbits.LATB9 = 1;
						LATBbits.LATB10 = 0;
						LATBbits.LATB11 = 0;
						LATBbits.LATB12 = 0;
						LATBbits.LATB13 = 0;
						LATBbits.LATB14 = 0; break;
			
			case 'c':  	LATBbits.LATB8 = 0;
						LATBbits.LATB9 = 0;
						LATBbits.LATB10 = 1;
						LATBbits.LATB11 = 0;
						LATBbits.LATB12 = 0;
						LATBbits.LATB13 = 0;
						LATBbits.LATB14 = 0; break;
			
			case 'd':  	LATBbits.LATB8 = 0;
						LATBbits.LATB9 = 0;
						LATBbits.LATB10 = 0;
						LATBbits.LATB11 = 1;
						LATBbits.LATB12 = 0;
						LATBbits.LATB13 = 0;
						LATBbits.LATB14 = 0; break;
			
			case 'e':  	LATBbits.LATB8 = 0;
						LATBbits.LATB9 = 0;
						LATBbits.LATB10 = 0;
						LATBbits.LATB11 = 0;
						LATBbits.LATB12 = 1;
						LATBbits.LATB13 = 0;
						LATBbits.LATB14 = 0; break;
			
			case 'f':  	LATBbits.LATB8 = 0;
						LATBbits.LATB9 = 0;
						LATBbits.LATB10 = 0;
						LATBbits.LATB11 = 0;
						LATBbits.LATB12 = 0;
						LATBbits.LATB13 = 1;
						LATBbits.LATB14 = 0; break;
			
			case 'g':  	LATBbits.LATB8 = 0;
						LATBbits.LATB9 = 0;
						LATBbits.LATB10 = 0;
						LATBbits.LATB11 = 0;
						LATBbits.LATB12 = 0;
						LATBbits.LATB13 = 0;
						LATBbits.LATB14 = 1; break;
		}
	}
}
