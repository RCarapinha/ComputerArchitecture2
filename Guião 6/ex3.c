#include <detpic32.h>
void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);    
    }
}

void main(void){
    //Configurar tudo
    TRISBbits.TRISB4 = 1;//Desliga entrada digital
    AD1PCFGbits.PCFG4 = 0;//Configura como entrada analogica
    AD1CON1bits.SSRC= 7;//Configurar trigger do processo de ínicio de conversão para "auto convert"
    AD1CON1bits.CLRASAM = 1;//Determina que o processo de conversão só começa quando é dada a ordem de ínicio de conversão
    AD1CON3bits.SAMC = 16;//Configurar duração do tempo de amostragem (16 = 1600ns)
    AD1CON2bits.SMPI = 0;//Configurar nr de conversão consecutivas do mesmo canal
    AD1CHSbits.CH0SA = 4;//Entrada analógica a converter, canal de entrada (AN4 -> RB4)
    AD1CON1bits.ON = 1;//Ativa conversor A/D
    //Configurar sistema de interrupçoes
    IPC6bits.AD1IP = 2;//Configurar prioridade
    IEC1bits.AD1IE = 1;//Ativar interrupções A/D
    IFS1bits.AD1IF = 0;//Reset da flag
    EnableInterrupts();//Ativar interrupções globalmente
    //Começar conversor A/D
    AD1CON1bits.ASAM = 1;
    while(1){
        LATBbits.LATB6 = 0;    
    }
}

void _int_(27) isr_adc(void){
    //ISR actions
    printInt(&ADC1BUF0, 16 | 3 << 16); //Hexadecimal, com 3 digitos
    printf("\n");
    LATBbits.LATB6 = 0;
    //Começar conversor A/D
    AD1CON1bits.ASAM = 1;
    IFS1bits.AD1IF = 0;
    LATBbits.LATB6 = 1;
}
