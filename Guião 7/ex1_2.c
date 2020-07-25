#include <detpic32.h>
void main(void){
    //K_PRESCALER >= [fPBCLK/(65536*fOUT)]
    //TEMOS DE USAR KPRECALER MAIS PROXIMO E MAIOR QUE O VALOR QUE NOS DEU EM CIMA
    //TIMER A -> T1 -> 1,8,64,256
    //TIMER B -> T2,T3,T4,T5 -> 1,2,4,8,16,32,64,256
    //fOUT_PRESCALER = fPBCLK/KPRESCALER
    //PR2 = (fOUT_PRESCALER/fOUT)-1
    T3CONbits.TCKPS = 7;//1:256    
    PR3 = 39062;
    TMR3 = 0;//Reset timer 3 count register
    T3CONbits.TON = 1;//Enbale timer

    IPC3bits.T3IP = 2;//Prioridade
    IEC0bits.T3IE = 1;//Enable Interrupts timer t3
    IFS0bits.T3IF = 0;//Reset Interrupt Flag
    EnableInterrupts();
    while(1){ }
}

void _int_ (17) isr_T3(void){
    putChar('.');
    IFS0bits.T3IF = 0;
}
