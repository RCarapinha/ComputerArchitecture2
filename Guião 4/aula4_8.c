#include <detpic32.h>
void delay(int);

void main(void){
    static const char display7Scodes[] = {0x3F, 0x06, 0x5B,...};
    // configure RB0 to RB3 as inputs
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
    while(1){
       // read dip-switch
       // convert to 7 segments code
       // send to display
    }
}

void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);
    }
}
