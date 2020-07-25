#include <detpic32.h>
void delay(int);

void main(void){
    LATEbits.LATE0 = 0;
    LATEbits.LATE1 = 0;
    LATEbits.LATE2 = 0;
    LATEbits.LATE3 = 0;
    
    TRISEbits.TRISE0 = 0;
    TRISEbits.TRISE1 = 0;
    TRISEbits.TRISE2 = 0;
    TRISEbits.TRISE3 = 0;
    
    int i = 0;   
    while(1){
        LATE = i;
        delay(500); // half period = 0.5s
        i = i + 1;
    }
}

void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);
    }
}  
