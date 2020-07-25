#include <detpic32.h>
void delay(int);
void putc(char);
void puts(char*);
void ConfigUART(unsigned int, char, unsigned int);

int main (void){    
    ConfigUART(0,'O',0);
    while(1){
        puts("String de Teste \n");
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

void puts(char *str){
   int i = 0;
   while(str[i] != '\0'){
       putc(str[i]);
       i++;
   }
}

void ConfigUART(unsigned int BAUDRATE, char Parity, unsigned int STOP){
    //BAUDRATE
  
    if(BAUDRATE < 600 || BAUDRATE > 115200){
        BAUDRATE = 115200;        
    }

    U1BRG=((PBCLK+8*BAUDRATE)/(16*BAUDRATE))-1;
    U1MODEbits.BRGH=0; //Fator de divisão 16; 0 -> FATOR DIVISÃO 16    

    //PARIDADE
  
    switch(Parity){
        case 'N': U1MODEbits.PDSEL=00; break; //8BIT DATA, NO PARITY
        case 'E': U1MODEbits.PDSEL=01; break; //8BIT DATA, EVEN PARITY
        case 'O': U1MODEbits.PDSEL=10; break; //8BIT DATA, ODD PARITY
        default:  U1MODEbits.PDSEL=00; break;
    }

    //STOP BITS
    
    U1MODEbits.STSEL=(--STOP);
    
    U1STAbits.UTXEN=1; //Ativar modulo transmissão
    U1STAbits.URXEN=1; //Ativar modulo receção

    U1MODEbits.ON=1; //Ativar UART
}
