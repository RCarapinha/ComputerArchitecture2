#include <detpic32.h>
#define DisableUart1RxInterrupt() IEC0bits.U1RXIE = 0
#define EnableUart1RxInterrupt() IEC0bits.U1RXIE = 1

#define DisableUart1TxInterrupt() IEC0bits.U1TXIE = 0
#define EnableUart1TxInterrupt() IEC0bits.U1TXIE = 1

#define BUF_SIZE 8
#define INDEX_MASK (BUF_SIZE-1)

typedef struct{
    unsigned char data[BUF_SIZE];
    unsigned char head;
    unsigned char tail;
    unsigned char count;
} circularBuffer;

volatile circularBuffer txb;
volatile circularBuffer rxb;

void comDrv_flushRx(void){
    int i;    
    
    rxb.tail = 0;
    rxb.head = 0;
    rxb.count = 0;

    for(i=0;i<BUF_SIZE;i++){
        rxb.data[i]=0;
    }
}

void comDrv_flushTx(void){
    int i;    
    
    txb.tail = 0;
    txb.head = 0;
    txb.count = 0;

    for(i=0;i<BUF_SIZE;i++){
        txb.data[i]=0;
    }
}

void comDrv_putc(char ch){
    while(txb.count == BUF_SIZE);//Espera que o Buffer não esteja cheio, não podemos realizar putc (vamos acrescentar quando esta cheio)
    txb.data[txb.tail]=ch;//Ponho caracter no tail

    txb.tail = (txb.tail+1) & INDEX_MASK;//Incrementa tail e dá a volta;

    DisableUart1TxInterrupt();//Inicio Secção Critica
    txb.count += 1;//Incrementa Count
    EnableUart1TxInterrupt();//Fim Secção Critica 
}

void comDrv_puts(char* ch){
    int i = 0;
    while(ch[i] != '\0'){
        comDrv_putc(ch[i]);
        i += 1;   
    }
}

void _int_(24) isr_uart1(void){
    if(IFS0bits.U1TXIF == 1){
        if(txb.count > 0){
            U1TXREG = txb.data[txb.head];
            txb.head = (txb.head+1) & INDEX_MASK;
            txb.count--;  
        }
        if(txb.count == 0){
            DisableUart1TxInterrupt();        
        }   
    }
    IFS0bits.U1TXIF = 0;

    if(IFS0bits.U1RXIF){
		rxb.data[rxb.tail] = U1RXREG;
	    rxb.tail = (rxb.tail + 1) & INDEX_MASK;
		if(rxb.count < BUF_SIZE){
			rxb.count++;
		}else{
			rxb.head++;
		}
        IFS0bits.U1RXIF = 0;
	}
}

void comDrv_config(unsigned int BAUDRATE, char Parity, unsigned int STOP){
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

    DisableUart1TxInterrupt();
	DisableUart1RxInterrupt();

	IPC6bits.U1IP = 3;

	U1STAbits.URXISEL = 00;
}

char comDrv_getc(char *pchar){
    if(rxb.count == 0){
        return 0;    
    }
    DisableUart1RxInterrupt();
    *pchar = rxb.data[rxb.head];
    rxb.count--;
    rxb.head = (rxb.head+1) & INDEX_MASK;
    EnableUart1RxInterrupt();
    return 1;
}

void main(void){
    comDrv_config(115200,'N',1);
    comDrv_flushRx();
    comDrv_flushTx();
    EnableInterrupts();
    comDrv_puts("Teste do bloco de transmissão do device driver.\n");  
    char c;    
    while(1){
        c = comDrv_getc(&c);
        comDrv_putc(c);
    }
}
