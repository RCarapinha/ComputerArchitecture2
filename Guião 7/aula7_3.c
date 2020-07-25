#include <detpic32.h>
int Gay = 1;
void main(void){
    T3CONbits.TCKPS=7; //1:256
    PR3=39062;
    TMR3=0;
    T3CONbits.TON=1;
    IPC3bits.T3IP=2;
	IEC0bits.T3IE=1;
	IFS0bits.T3IF=0;
    EnableInterrupts();
    while(1){
	}
}

void _int_(12) isr_T3(void){
	if(Gay){
		putChar('.');
		Gay = 0;
	}else{
		Gay = 1;
	}
	IFS0bits.T3IF = 0;
}
