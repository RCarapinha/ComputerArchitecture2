#include <detpic32.h>
void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);    
    }
}

void main(void){
    TRISBbits.TRISB4 = 1;//Desliga entrada digital
    AD1PCFGbits.PCFG4 = 0;//Configura como entrada analogica
    AD1CON1bits.SSRC= 7;//Configurar trigger do processo de ínicio de conversão para "auto convert"
    AD1CON1bits.CLRASAM = 1;//Determina que o processo de conversão só começa quando é dada a ordem de ínicio de conversão
    AD1CON3bits.SAMC = 16;//Configurar duração do tempo de amostragem (16 = 1600ns)
    AD1CON2bits.SMPI = 0;//Configurar nr de conversão consecutivas do mesmo canal
    AD1CHSbits.CH0SA = 4;//Entrada analógica a converter, canal de entrada (AN4 -> RB4)
    AD1CON1bits.ON = 1;//Ativa conversor A/D
    while(1){
        AD1CON1bits.ASAM=1;//Começa conversão
        while(IFS1bits.AD1IF==0);//Espera enquanto conversão não está feita
        delay(500);        
        printInt10(ADC1BUF0);    
        printf("\n");
        IFS1bits.AD1IF=0;//Reset bit
    }
}
