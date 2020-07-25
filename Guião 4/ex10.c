#include <detpic32.h>
void send2display(int);
void main(void){
    TRISB = 0x000F;

    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;

    int a, b, c, d, n = 0;  
    while(1){
        a = PORTBbits.RB0; 
        b = PORTBbits.RB1;
        c = PORTBbits.RB2;
        d = PORTBbits.RB3;       
        n = a+2*b+4*c+8*d;
        send2display(n);
    }
}

void send2display(int value){
    static const char display7SCodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};  
    LATB = display7SCodes[value]<<8;
}
