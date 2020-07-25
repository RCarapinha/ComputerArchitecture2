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
