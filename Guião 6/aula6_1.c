#include <detpic32.h>
void delay(int);

void main(void){
	//Configure all
    TRISBbits.TRISB4 = 1; //Desliga entrada digital
    AD1PCFGbits.PCFG4 = 0; //Configurar como entrada analógica
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 0;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;  
    //Configure interrup system
    IPC6bits.AD1IP = 2; //Prioridade
    IEC1bits.AD1IE = 1; //Autoriza interrupções
    IFS1bits.AD1IF = 0; //Clear da interrupção 
    EnableInterrupts();
    //Starts A/D Conversion
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
	delay(1000);
	printInt(ADC1BUF0, 16 | 3 << 16);
	printf("\n");
	AD1CON1bits.ASAM = 1; //Start A/D Conversion
	IFS1bits.AD1IF = 0; //Reset AD1IF flag
} 
