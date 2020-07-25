#include <detpic32.h>
void delay(int);
int int2BCD (unsigned int);
void send2displays (int);
void selectdisp (int,int);

volatile int voltage = 0;
int i = 0;

void main(void){
	TRISB &= 0x00FF;   //RB4 as digital output disconnected
	TRISD &= 0xFF9F; 
	AD1PCFG &= 0xFFEF; //RB4 configured as analog input
	TRISBbits.TRISB1 = 1;
	TRISBbits.TRISB0 = 1;
		
	
	//Timer 3 Tipo B
    T3CONbits.TCKPS=2; //1:4
    PR3=49999;
    TMR3=0;
    T3CONbits.TON=1;
    IPC3bits.T3IP=3;
	IEC0bits.T3IE=1;
	IFS0bits.T3IF=0;
	
	//Timer 1 Tipo A
	T1CONbits.TCKPS=7; //1:256
    PR1=19530;
    TMR1=0;
    T1CONbits.TON=1;
    IPC1bits.T1IP=3;
	IEC0bits.T1IE=1;
	
	//AD1 Config
	AD1PCFGbits.PCFG4 = 0;
	AD1CON1bits.SSRC = 7;
	AD1CON1bits.CLRASAM = 1;
	AD1CON3bits.SAMC = 16;
	AD1CON2bits.SMPI = 3;
	AD1CHSbits.CH0SA = 4;
	AD1CON1bits.ON = 1;
	IPC6bits.AD1IP = 2;
    IEC1bits.AD1IE = 1;
    
    //Reset Flags
    IFS1bits.AD1IF=0; 
	IFS0bits.T3IF=0;
	IFS0bits.T1IF=0;
    
    EnableInterrupts();
    
	while(1){ }
}

void delay(int ms){
	for(; ms > 0; ms--){
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}

void _int_(12) isr_T3(void){
	send2displays(voltage);
	IFS0bits.T3IF = 0;
}

void _int_(4) isr_T1(void){
	if(PORTBbits.RB1 == 0 && PORTBbits.RB0 == 1){
		AD1CON1bits.ASAM = 0;
	}else{
		AD1CON1bits.ASAM = 1;
	}
	IFS0bits.T1IF = 0;
}

void _int_(27) isr_adc(void){
	int j;
	int soma = 0;
	int media = 0;
	double V;
	double amplitude = 0;
	
	int *p = (int *)(&ADC1BUF0);
	
	for(j = 0;j< 4;j++){
		soma += p[j*4];
	}
	
	media = soma/4;
	V= (media*33)/1023;
	amplitude = 33-V;
		
	voltage = int2BCD((unsigned int)(amplitude));
	
	IFS1bits.AD1IF = 0;
}

int int2BCD (unsigned int valor){
	int aux = 0;
	aux = ((valor / 10) << 4 | (valor % 10));
	return ((int)(aux));
}

void send2displays(int valor){
	
	static const int display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 
						0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
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

void selectdisp (int disp, int c){
	if(disp){
		LATD = 0x40;
	}
	else{
		LATD = 0x20;
	}
	LATB = c;
}
