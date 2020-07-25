#include <detpic32.h>
void main(void){
    TRISB = 0x000F;

    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    
    LATDbits.LATD5 = 0;
    LATDbits.LATD6 = 1;

    int a, b, c, d, n;
    static const char display7SCodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};  
    while(1){
        a = PORTBbits.RB0; 
        b = PORTBbits.RB1;
        c = PORTBbits.RB2;
        d = PORTBbits.RB3;       
        n = a+2*b+4*c+8*d;
        LATB = display7SCodes[n]<<8;
    }
}  
