#include <detpic32.h>
int Gay = 1;
void main(void){
    //Timer 3 Tipo B
    T3CONbits.TCKPS=5; //1:32
    PR3=62499;
    TMR3=0;
    T3CONbits.TON=1;
    IPC3bits.T3IP=2;
	IEC0bits.T3IE=1;
	IFS0bits.T3IF=0;
	
	//Timer 1 Tipo A
	T1CONbits.TCKPS=3; //1:256
    PR1=39062;
    TMR1=0;
    T1CONbits.TON=1;
    IPC1bits.T1IP=2;
	IEC0bits.T1IE=1;
	
	IFS0bits.T3IF=0;
	IFS0bits.T1IF=0;
	
    EnableInterrupts();
    while(1){
	}
}

void _int_(12) isr_T3(void){
	putChar('3');
	IFS0bits.T3IF = 0;
}

void _int_(4) isr_T1(void){
	printf(" 1 ");
	IFS0bits.T1IF = 0;
}

