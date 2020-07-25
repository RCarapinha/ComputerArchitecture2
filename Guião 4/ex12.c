#include <detpic32.h>
void selectdisp (int disp, int c){
	if(disp){
		LATD = 0x40;
	}
	else{
		LATD = 0x20;
	}
	LATB = c;
}

void send2displays(int valor){
	
	static const int display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
	static unsigned int sel = 1;
	int hi  = 0x0000;
	int low = 0x0000;					
	
	hi = display7Scodes[valor >>4];
	low = display7Scodes[valor & 0xF];


	if(!sel){
		selectdisp(sel,(low << 8));
	}
	else{
		selectdisp(sel,(hi << 8));	
	}	
	sel = !sel;								
}

unsigned char toBcd(unsigned char value){
    return ((value / 10) << 4) + (value % 10);
}

void main(void){
    int a, b, c, d, n = 0;
    unsigned char p; 
    while(1){
        a = PORTBbits.RB0; 
        b = PORTBbits.RB1;
        c = PORTBbits.RB2;
        d = PORTBbits.RB3;       
        n = a+2*b+4*c+8*d;
        send2displays(n);
    }
}
