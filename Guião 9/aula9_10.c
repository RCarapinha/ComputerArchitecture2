#include <detpic32.h>
#define DisableUart1RxInterrupt() IEC0bits.U1RXIE=0
#define EnableUart1RxInterrupt() IEC0bits.U1RXIE=1
#define DisableUart1TxInterrupt() IEC0bits.U1TXIE=0
#define EnableUart1TxInterrupt() IEC0bits.U1TXIE=1
#define BUF_SIZE 8
#define INDEX_MASK (BUF_SIZE-1)

void delay(unsigned int);

typedef struct{
    unsigned char data[BUF_SIZE];
    unsigned int head;
    unsigned int tail;
    unsigned int count;
} circularBuffer;

volatile circularBuffer rxb;
volatile circularBuffer txb;

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
    while(txb.count == BUF_SIZE){} //Espera que o Buffer não esteja cheio, não podemos realizar putc (vamos acrescentar quando esta cheio)

    txb.data[txb.tail] = ch; //Ponho caracter no tail
    txb.tail = (txb.tail+1) & INDEX_MASK; //Incrementa tail e dá a volta;
    
    DisableUart1TxInterrupt(); //Inicio Secção Critica
    txb.count++; //Incrementa Count
    EnableUart1TxInterrupt(); //Fim Secção Critica
}

void comDrv_puts(char *s){
    while(*s != '\0'){
        comDrv_putc(*s);
        s++;
    }
}

void _int_(24) isr_uart1(void){
    if(IFS0bits.U1TXIF == 1){
        if(txb.count > 0){
            U1TXREG = txb.data[txb.head];
            txb.head = (txb.head+1) & INDEX_MASK;
            txb.count--;
        }
        else if(txb.count == 0){
            DisableUart1TxInterrupt();           
        }
        IFS0bits.U1TXIF = 0;    
    }

    if(IFS0bits.U1RXIF == 1){
        rxb.data[rxb.head]=U1RXREG;
        rxb.tail = (rxb.tail+1) & INDEX_MASK;
        if(rxb.count < BUF_SIZE){
            rxb.count++;
        }else{
            rxb.head++;        
        }
        IFS0bits.U1RXIF = 0;    
    }
}

void comDrv_config(unsigned int baud, char parity, unsigned int Stopbits){
	if(baud<600 || baud > 115200){
		baud = 115200;
	}
	
    if(parity!='N' && parity!='E' && parity!='O'){
		parity = 'N';
	}
    
    if(Stopbits!=1 && Stopbits!=2){
		Stopbits = 1;
	}

	U1BRG = ((20000000 + 8*baud)/ (16*baud))-1;
	U1MODEbits.BRGH = 0;

	if(parity=='N'){
		U1MODEbits.PDSEL = 00;
	}else if(parity=='E'){
		U1MODEbits.PDSEL = 01;
	}else if(parity=='O'){
		U1MODEbits.PDSEL = 10;
	}

	/*
	PDSEL<1:0>: Parity and Data Selection bits
	11 = 9-bit data, no parity
	10 = 8-bit data, odd parity
	01 = 8-bit data, even parity
	00 = 8-bit data, no parity
	*/

	U1MODEbits.STSEL = (--Stopbits);

	/*
	STSEL: Stop Selection bit
	1 = 2 Stopbits
	0 = 1 Stopbit
	*/

	U1STAbits.UTXEN = 1;
	U1STAbits.URXEN = 1;

	U1MODEbits.ON = 1;

    //ALTERAÇÕES
    DisableUart1TxInterrupt();
	DisableUart1RxInterrupt();

	//a definição da prioridade devem ser configurados os 3 bits UxIP (a configuração de prioridade é comum a todas as fontes de interrupção de uma UART)
	IPC6bits.U1IP = 3;

	//URXISEL<1:0> do registo UxSTA -> O modo como as interrupções são geradas
	U1STAbits.URXISEL = 00;
	
    //UrXISEL<1:0> do registo UxSTA -> O modo como as interrupções são geradas
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

void delay(unsigned int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);
    }
}

int main (void){
    comDrv_config(115200, 'N', 1);
    comDrv_flushRx();
    comDrv_flushTx();
    char var;
    EnableInterrupts();
    comDrv_puts("PIC32 UART Device-Driver\n");
    while(1){
        if(comDrv_getc(&var)){
            comDrv_puts("FALSE\n");
        }else{
            comDrv_puts("TRUE\n");
        }
        delay(500);    
    }
}
