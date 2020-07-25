#include <detpic32.h>
void delay(int);
void putc(char);

int main (void){
    U1MODEbits.BRGH=0; //Fator de divisão 16; 0 -> FATOR DIVISÃO 16
    int BAUDRATE=115200;

    U1BRG=((PBCLK+(8*BAUDRATE))/(16*BAUDRATE)-1);
    U1MODEbits.PDSEL=00; //Nr bits paridade; 00->8BIT-DATA, NO PARITY
    U1MODEbits.STSEL=0; //Nr stop bits; 0->1 stop bit
    
    U1STAbits.UTXEN=1; //Ativar modulo transmissão
    U1STAbits.URXEN=1; //Ativar modulo receção

    U1MODEbits.ON=1; //Ativar UART

    //N-No parity
    //O-Odd parity
    //E-Even parity

    while(1){
        putc('+');
        delay(1000);    
    }
}

void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);
    }
}

void putc(char byte2send){
   while(U1STAbits.UTXBF == 1);
   U1TXREG=byte2send;
} 
