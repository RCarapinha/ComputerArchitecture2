#include <detpic32.h>
void delay(int);

void main(void){
	LATBbits.LATB6 = 0;
	
	TRISBbits.TRISB6 = 0;
    TRISBbits.TRISB4 = 1; //Desliga entrada digital
    AD1PCFGbits.PCFG4 = 0; //Configurar como entrada analógica
    AD1CON1bits.SSRC = 7;
    
    AD1CON1bits.CLRASAM = 1;
    
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 0;
    
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;  
    
    volatile int aux; 
    while(1){
		LATBbits.LATB6 = 1;
		AD1CON1bits.ASAM = 1; 
		while(IFS1bits.AD1IF == 0);
		LATBbits.LATB6 = 0;
		delay(1000);
		aux = ADC1BUF0;
		printInt(aux, 16 | 3 << 16);
		printf("\n");
		IFS1bits.AD1IF = 0;
    }
}

void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);
    }
}  
