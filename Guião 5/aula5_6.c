#include <detpic32.h>
void delay(int);
void displayChar(int);

void main(void){
	LATBbits.LATB15 = 0;
    LATBbits.LATB14 = 0;
    LATBbits.LATB13 = 0;
    LATBbits.LATB12 = 0;
    LATBbits.LATB11 = 0;
    LATBbits.LATB10 = 0;
    LATBbits.LATB9 = 0;
    LATBbits.LATB8 = 0;

    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 1;

    TRISBbits.TRISB15 = 0;
    TRISBbits.TRISB14 = 0;
    TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB12 = 0;
    TRISBbits.TRISB11 = 0;
    TRISBbits.TRISB10 = 0;
    TRISBbits.TRISB9 = 0;
    TRISBbits.TRISB8 = 0;
    
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
	 
    TRISBbits.TRISB4 = 1; //Desliga entrada digital
    AD1PCFGbits.PCFG4 = 0; //Configurar como entrada analógica
    AD1CON1bits.SSRC = 7;
    
    AD1CON1bits.CLRASAM = 1;
    
    AD1CON3bits.SAMC = 16;
    AD1CON2bits.SMPI = 15; //Conversões consetcutivas X-1
    //Exercicio 5 com 4 amostras (original)
    AD1CHSbits.CH0SA = 4;
    AD1CON1bits.ON = 1;  

    volatile int aux; 
    int i = 0;
    int j;
    int soma = 0;
    double media;
    int V = 0;
    
    while(1){
		AD1CON1bits.ASAM = 1; 
		while(IFS1bits.AD1IF == 0);
		
		delay(10);
		if(++i==25){		
			int *p = (int *)(&ADC1BUF0);
			for(j = 0; j < 16; j++){
				aux = p[j*4];
				soma = soma + aux;
			}
			media = soma/16;
			V = (int)(media*33)/1023;
            printf("%d", V);
            printf("\n");
			i = 0;	
			soma = 0;
            IFS1bits.AD1IF = 0;
		}
		displayChar(V);
	}
}

void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);
    }
}

void displayChar(int c){
    LATDbits.LATD6 = !LATDbits.LATD6;
    LATDbits.LATD5 = !LATDbits.LATD5;
}  
