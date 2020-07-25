#include <detpic32.h>
void delay(int);

void main(void){
	
	LATBbits.LATB6 = 0;
	TRISBbits.TRISB6 = 0;
	//Configure All
	TRISBbits.TRISB4 = 1;
	AD1PCFGbits.PCFG4 = 0;
	AD1CON1bits.SSRC = 7;
	
	AD1CON1bits.CLRASAM = 1;
	
	AD1CON3bits.SAMC = 16;
	AD1CON2bits.SMPI = 0;
	
	AD1CHSbits.CH0SA = 4;
	
	AD1CON1bits.ON = 1;
	//Configure Interrupt System
	IPC6bits.AD1IP = 2; //Prioridade
    IEC1bits.AD1IE = 1; //Autoriza interrupções
    IFS1bits.AD1IF = 0; //Clear da interrupção 
	EnableInterrupts();
	//Start A/D Conversion
	AD1CON1bits.ASAM = 1;
	while(1){ }
}

void delay(int ms){
	for(; ms > 0; ms--){
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}

void _int_(27) isr_adc(void){
	LATBbits.LATB6 = 0;
	delay(1000);
	printInt(ADC1BUF0, 16 | 3 << 16);
	printf("\n");
	LATBbits.LATB6 = 1;
	AD1CON1bits.ASAM = 1;
	IFS1bits.AD1IF = 0;
}
