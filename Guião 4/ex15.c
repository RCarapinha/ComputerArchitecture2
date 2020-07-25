#include <detpic32.h>

void send2displays(unsigned char value){
	static unsigned char displayFlag = 0;
	static const unsigned char codes[] = {0x77, 0x41, 0x3B, 0x6B, 0x4D, 0x6E, 0x7E, 0x43, 0x7F, 0x6F, 0x5F, 0x7C, 0x36, 0x79, 0x3E, 0x1E};
    TRISB = 0x000F;    

	unsigned char first = value & 0x0F;
	first = codes[first];
	unsigned char second = (value >> 4);
	second = codes[second];

	if (!displayFlag){
		LATDbits.LATD5 = 0;
		LATDbits.LATD6 = 1;
		LATB = (LATB & 0x000F) | first;
	}else{
		LATDbits.LATD5 = 1;
		LATDbits.LATD6 = 0;
		LATB = (LATB & 0x000F) | second;
	}

	displayFlag = !displayFlag;
}

unsigned char toBcd(unsigned char value){
    return ((value / 10) << 4) + (value % 10);
}

void delay(int ms){
    for(;ms<0;ms--){
        resetCoreTimer();
        while(readCoreTimer()<20000);    
    }
}

int main(void){
	unsigned char c = 0, tmp;
	int i;

	while(1){
		i = 0;
		do{
			delay(10);
			tmp = toBcd(c);
			send2displays(tmp);
		}while(++i<4);
		if(c==0x3B){
			c = 0;
			do{
				i = 0;
				do{
					delay(10);
					send2displays(0);
				}while(++i<50);
				/* limpar o display */
				LATB = LATB & 0xFC00; /* colocar tudo a 0 => a mascara foi alterada para o bit 7 ser definido antes */
				/* esperar 500 ms */
				delay(500);
			}while(++c<5);
			c = 0;
		}else{
			c++;
		}
	};
	return 0;
}
