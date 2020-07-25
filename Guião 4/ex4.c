#include <detpic32.h>
void delay(int);
void displayChar(int);

void main(void){
    unsigned int segment;
    LATDbits.LATD6 = 1; // display high active
    LATDbits.LATD5 = 0; // display low inactive

    TRISBbits.TRISB14 = 0;
    TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB12 = 0;
    TRISBbits.TRISB11 = 0;
    TRISBbits.TRISB10 = 0;
    TRISBbits.TRISB9 = 0;
    TRISBbits.TRISB8 = 0;
    
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    
    int i = 0;
    while(1){
        LATDbits.LATD6 = !LATDbits.LATD6; //
        LATDbits.LATD5 = !LATDbits.LATD5; // toggle display selection
        segment = 1;
        for(i=0; i < 7; i++){
            displayChar(segment);// send "segment" value to display
            delay(1000);
            segment = segment + 1;
        }
    }
} 

void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);
    }
}  

void displayChar(int c){
	if(c==1){
		LATB=0x7700;
	}else if(c==2){
		LATB=0x7C00;
	}else if(c==3){
		LATB=0x3900;
	}else if(c==4){
		LATB=0x5E00;
	}else if(c==5){
		LATB=0x7900;
	}else if(c==6){
		LATB=0x7100;
	}else if(c==7){
		LATB=0x7100;
    }
}
