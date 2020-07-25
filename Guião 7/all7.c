//Exercicio 1.1

#include <detpic32.h>
void main(void){
    //K_PRESCALER >= [fPBCLK/(65536*fOUT)]
    //TEMOS DE USAR KPRECALER MAIS PROXIMO E MAIOR QUE O VALOR QUE NOS DEU EM CIMA
    //TIMER A -> T1 -> 1,8,64,256
    //TIMER B -> T2,T3,T4,T5 -> 1,2,4,8,16,32,64,256
    //fOUT_PRESCALER = fPBCLK/KPRESCALER
    //PR2 = (fOUT_PRESCALER/fOUT)-1
    T3CONbits.TCKPS = 7;    
    PR3 = 39062;
    TMR3 = 0;
    T3CONbits.TON = 1;
    while(1){
        while(IFS0bits.T3IF == 0);
        IFS0bits.T3IF = 0;
        putChar('.');
    }
}

//Exercicio 1.2

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

void _int_ (12) isr_T3(void){
    putChar('.');
    IFS0bits.T3IF = 0;
}

//Exercicio 1.3

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

void _int_ (12) isr_T3(void){
    putChar('.');
    IFS0bits.T3IF = 0;
}

//Exercicio 1.4

#include <detpic32.h>
void main(void){
    //K_PRESCALER >= [fPBCLK/(65536*fOUT)]
    //TEMOS DE USAR KPRECALER MAIS PROXIMO E MAIOR QUE O VALOR QUE NOS DEU EM CIMA
    //TIMER A -> T1 -> 1,8,64,256
    //TIMER B -> T2,T3,T4,T5 -> 1,2,4,8,16,32,64,256
    //fOUT_PRESCALER = fPBCLK/KPRESCALER
    //PR2 = (fOUT_PRESCALER/fOUT)-1
    T1CONbits.TCKPS = 3;//1:256    
    PR1 = 39062;
    TMR1 = 0;//Reset timer 1 count register
    T1CONbits.TON = 1;//Enable timer

    T3CONbits.TCKPS = 5;//1:32    
    PR3 = 62499;
    TMR3 = 0;//Reset timer 3 count register
    T3CONbits.TON = 1;//Enable timer
    
    IPC1bits.T1IP = 2;//Prioridade
    IEC0bits.T1IE = 1;//Enable Interrupts timer t1
    IFS0bits.T1IF = 0;//Reset Interrupt Flag

    IPC3bits.T3IP = 2;//Prioridade
    IEC0bits.T3IE = 1;//Enable Interrupts timer t3
    IFS0bits.T3IF = 0;//Reset Interrupt Flag

    EnableInterrupts();
    while(1){ }
}

void _int_ (12) isr_T3(void){
    putChar('3');
    IFS0bits.T3IF = 0;
}

void _int_ (4) isr_T1(void){
    printf("\n");
    putChar('1');
    printf("\n");
    IFS0bits.T1IF = 0;
}
