#include <detpic32.h>

void main(void){
    //Baudrate generator    
    U1BRG = ((PBCLK+(8*115200))/(16*115200)-1);//No caso de 16 -> UxBRG = ((fPBCLK+8*baudrate)/(16*baudrate))-1
    //nr of data bits, parity, nr of stop bits
    U1MODEbits.BRGH = 0;//Fator de divisão 16
    U1MODEbits.PDSEL = 00;//Parity. 00 -> 8 bits, without parity
    U1MODEbits.STSEL = 0;//Stop bits. 0 -> 1 SB
    //TX and RX Modules
    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;
    //Enable UART
    U1MODEbits.ON = 1;
    while(1){
    }
}
