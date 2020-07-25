//Exercicio 1.1

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

//Exercicio 1.2

#include <detpic32.h>

void delay(int ms){
    for(; ms < 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);    
    }
}

void putc(char byte2send){
    while(U1STAbits.UTXBF == 1);
    U1TXREG = byte2send;
}

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
	delay(1000);
        putc('+');
    }
}

//Exercicio 1.3

#include <detpic32.h>

void delay(int ms){
    for(; ms > 0; ms--){
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
        puts("String de teste\n");
        delay(1000);
    }
}

//Exercicio 1.4

#include <detpic32.h>

void delay(int ms){
    for(; ms > 0; ms--){
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

void main(void){
    ConfigUART(115200, 'N', 1);
    while(1){
        puts("String de teste\n");
        delay(1000);
    }
}

//Exercicio 1.6

#include <detpic32.h>

void delay(int ms){
    for(; ms > 0; ms--){
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

void main(void){
    ConfigUART(115200, 'N', 1);
    while(1){
        while(U1STAbits.TRMT == 1);
        LATBbits.LATB6 = 1;
        puts("12345");
        LATBbits.LATB6 = 0;
    }
}

//Exercicio 1.9

#include <detpic32.h>

void delay(int ms){
    for(; ms > 0; ms--){
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
    ConfigUART(115200, 'N', 1);
    while(1){
        putc(getc());
    }
}

//Exercicio 2.2

#include <detpic32.h>

volatile unsigned char value2display = 0;
volatile int voltMin = 1000, voltMax = 0;
volatile double v = 0;

int int2BCD (unsigned int valor){
	int aux = 0;
	aux = ((valor / 10) << 4 | (valor % 10));
	return ((int)(aux));
}

void selectdisp (int disp, int c){
	if(disp){
		LATD = 0x40;
	}
	else{
		LATD = 0x20;
	}
	LATB = c;
}


void send2displays(int valor){
	static const int display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
	static unsigned int sel = 1;
	int hi  = 0x0000;
	int low = 0x0000;					
	
	hi = display7Scodes[valor >>4];
	low = display7Scodes[valor & 0xF];
	if(!sel){
		selectdisp(sel,(low << 8));
	}
	else{
		selectdisp(sel,(hi << 8));	
	}	
	sel=!sel;								
}
void delay(int ms){
    for(; ms > 0; ms--){
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
    ConfigUART(115200, 'N', 1);
    TRISB &= 0x00FF;
    TRISD &= 0xFF9F;
    
    //Configurar ADC
    TRISBbits.TRISB4 = 1;
    AD1PCFGbits.PCFG4 = 0;
    AD1CON1bits.SSRC = 7;
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 7;
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;
	
    IPC6bits.AD1IP = 2;
    IEC1bits.AD1IE = 1;

    //Configurar T3
    T3CONbits.TCKPS=2; //1:4
    PR3=49999;
    TMR3=0;
    T3CONbits.TON=1;
    IPC3bits.T3IP=3;
    IEC0bits.T3IE=1;

    //Configurar T1
    T1CONbits.TCKPS=7; //1:256
    PR1=19530;
    TMR1=0;
    T1CONbits.TON=1;
    IPC1bits.T1IP=3;
    IEC0bits.T1IE=1;

    //Configurar UART
    U1STAbits.URXISEL = 00;
    IEC0bits.U1RXIE = 1;
    IPC6bits.U1IP=3;
    IEC0bits.U1EIE = 1;
    ConfigUART(115200, 'N', 1);

    EnableInterrupts();
    while(1){
    }
}

void _int_(27) isr_adc(void){
    int *p = (int*)(&ADC1BUF0);
    int j = 0, soma = 0;
    double media;
    for(j = 0; j < 8; j++){
        soma += p[j*4];
    }
    media = soma/8;
    v = (media*33+511)/1023;
    if(v < voltMin){
	voltMin = v;
    }
    if(v > voltMax){
    	voltMax = v;
    }
    value2display = int2BCD((unsigned int)(v));
    soma = 0;
    IFS1bits.AD1IF = 0;
}

void _int_(24) isr_uart1(void){
	if(getc() == 'L'){
		puts("Voltagem Máxima -> ");
		printInt10(voltMax);
		puts("\n");
		puts("Voltagem Minima -> ");
		printInt10(voltMin);
		puts("\n");	
	}
	IFS0bits.U1RXIF = 0;
}

void _int_(4) isr_T1(void){
	AD1CON1bits.ASAM = 1; //Start conversion	
	IFS0bits.T1IF=0;
}

void _int_(12) isr_T3(void){
	static int counter = 0;
	send2displays(value2display);
	if(++counter == 100){
		counter = 0;
		puts("Voltagem -> ");
		printInt10(v);
		putc('\n');
		putc(U1TXREG);	
	}
	IFS0bits.T3IF = 0;
}
