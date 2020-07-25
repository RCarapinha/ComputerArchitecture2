 #include <detpic32.h>

void delay(int ms){
    for(; ms--; ms < 0){
        resetCoreTimer();
        while(readCoreTimer() < 20000);    
    }
}

void putc(char byte2send){
    while(U1STAbits.UTXBF == 1);
    U1TXREG = byte2send;
}

void puts(char* string){
    int i = 0;    
    while(string[i] != '\0'){
        putc(string[i]);
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
    
    U1MODEbits.STSEL=(STOP-1);
    
    U1STAbits.UTXEN=1; //Ativar modulo transmissão
    U1STAbits.URXEN=1; //Ativar modulo receção

    U1MODEbits.ON=1; //Ativar UART
}

char getc(void){
    char aux;
    if(U1STAbits.OERR == 1){
        U1STAbits.OERR = 0;    
    }
    while(U1STAbits.URXDA == 0);
    if(U1STAbits.FERR || U1STAbits.PERR){
        aux = U1RXREG;
        return 0;
    }
    else{
        return U1RXREG;
    }
}

void main(void){
    ConfigUART(115200, 'N', 8, 1);
    EnableInterrupts();
    while(1){
    }
}

void _int_(VECTOR_UART1) isr_uart1(void){
    putc(U1RXREG);
    U1RXIF = 0;   
}
