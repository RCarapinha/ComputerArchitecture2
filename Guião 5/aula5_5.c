#include <detpic32.h>
void delay(int);

void main(void){
	LATBbits.LATB6 = 0;
	
	TRISBbits.TRISB6 = 0;
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
    int i;
    int soma = 0;
    double media, V;
    
    while(1){
		LATBbits.LATB6 = 1;
		AD1CON1bits.ASAM = 1; 
		while(IFS1bits.AD1IF == 0);
		LATBbits.LATB6 = 0;
		
		int *p = (int *)(&ADC1BUF0);
		for(i = 0; i < 16; i++){
			aux = p[i*4];
			soma = soma + aux;
			printInt(aux, 10);
			printf(" ");
		}
		media = soma/16;
		V = (media*3.3)/1023;
		printf("\n");
		printf("Media = %4.2f", media);
		printf("\n");
		printf("Amplitude de Tensão = %4.1f", V);
		printf("\n");
		delay(1000);
		soma = 0;
		IFS1bits.AD1IF = 0;
    }
}

void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);
    }
}  
