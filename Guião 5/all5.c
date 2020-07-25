//Exercicio 1

#include <detpic32.h>
void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);    
    }
}

void main(void){
    TRISBbits.TRISB4 = 1;//Desliga entrada digital
    AD1PCFGbits.PCFG4 = 0;//Configura como entrada analogica
    AD1CON1bits.SSRC= 7;//Configurar trigger do processo de ínicio de conversão para "auto convert"
    AD1CON1bits.CLRASAM = 1;//Determina que o processo de conversão só começa quando é dada a ordem de ínicio de conversão
    AD1CON3bits.SAMC = 16;//Configurar duração do tempo de amostragem (16 = 1600ns)
    AD1CON2bits.SMPI = 0;//Configurar nr de conversão consecutivas do mesmo canal
    AD1CHSbits.CH0SA = 4;//Entrada analógica a converter, canal de entrada (AN4 -> RB4)
    AD1CON1bits.ON = 1;//Ativa conversor A/D
    while(1){
        AD1CON1bits.ASAM=1;//Começa conversão
        while(IFS1bits.AD1IF==0);//Espera enquanto conversão não está feita
        delay(500);        
        printInt10(ADC1BUF0);    
        printf("\n");
        IFS1bits.AD1IF=0;//Reset bit
    }
}

//Exercicio 3

#include <detpic32.h>
void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);    
    }
}

void main(void){
    int i = 0;
    volatile int aux;
    TRISBbits.TRISB4 = 1;//Desliga entrada digital
    AD1PCFGbits.PCFG4 = 0;//Configura como entrada analogica
    AD1CON1bits.SSRC= 7;//Configurar trigger do processo de ínicio de conversão para "auto convert"
    AD1CON1bits.CLRASAM = 1;//Determina que o processo de conversão só começa quando é dada a ordem de ínicio de conversão
    AD1CON3bits.SAMC = 16;//Configurar duração do tempo de amostragem (16 = 1600ns)
    AD1CON2bits.SMPI = 15;//Configurar nr de conversão consecutivas do mesmo canal
    AD1CHSbits.CH0SA = 6;//Entrada analógica a converter, canal de entrada (AN6)
    AD1CON1bits.ON = 1;//Ativa conversor A/D
    while(1){
        LATBbits.LATB6=1;
        AD1CON1bits.ASAM=1;//Começa conversão
        while(IFS1bits.AD1IF==0);//Espera enquanto conversão não está feita
        LATBbits.LATB6=0;        
        int *p = (int *)(&ADC1BUF0);
        for(i = 0; i < 16; i++){
            printInt(p[i*4], 10);
            printf(" ");
        }
	printf("\n");
	delay(250);
        IFS1bits.AD1IF=0;//Reset bit
    }
}

//Exercicio 5

 #include <detpic32.h>
void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);    
    }
}

void main(void){
    volatile int aux;
    double media;
    double v;
    int soma = 0, i;
    TRISBbits.TRISB4 = 1;//Desliga entrada digital
    AD1PCFGbits.PCFG4 = 0;//Configura como entrada analogica
    AD1CON1bits.SSRC= 7;//Configurar trigger do processo de ínicio de conversão para "auto convert"
    AD1CON1bits.CLRASAM = 1;//Determina que o processo de conversão só começa quando é dada a ordem de ínicio de conversão
    AD1CON3bits.SAMC = 16;//Configurar duração do tempo de amostragem (16 = 1600ns)
    AD1CON2bits.SMPI = 3;//Configurar nr de conversão consecutivas do mesmo canal
    AD1CHSbits.CH0SA = 4;//Entrada analógica a converter, canal de entrada (AN4)
    AD1CON1bits.ON = 1;//Ativa conversor A/D
    while(1){
        LATBbits.LATB6=1;
        AD1CON1bits.ASAM=1;//Começa conversão
        while(IFS1bits.AD1IF==0);//Espera enquanto conversão não está feita
        LATBbits.LATB6=0;        
        int *p = (int *)(&ADC1BUF0);
        for(i = 0; i < 4; i++){
            aux = p[i*4];
            soma += aux;
        }
        media = soma/4;
        v = (media*33+511)/1023;
        printf("v -> ");
        printf("%4.2f",v);
        printf("\n");
        delay(1000);
        soma = 0;
	    media = 0;        
        IFS1bits.AD1IF=0;//Reset bit
    }
}

//Exercicio 6

#include <detpic32.h>

void selectdisp (int disp, int c){
	if(disp){
		LATD = 0x40;
	}
	else{
		LATD = 0x20;
	}
	LATB = c;
}

int int2BCD (unsigned int valor){
	int aux = 0;
	aux = ((valor / 10) << 4 | (valor % 10));
	return ((int)(aux));
}

void send2displays(int valor){
	
	static const int display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 
						0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
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
	sel = !sel;								
}

void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);    
    }
}

void main(void){
    double media;
    double v = 0;
    int j = 0, i = 0;
    int soma = 0;
    TRISD &= 0xFF9F; 
    TRISBbits.TRISB4 = 1;//Desliga entrada digital
    AD1PCFGbits.PCFG4 = 0;//Configura como entrada analogica
    AD1CON1bits.SSRC= 7;//Configurar trigger do processo de ínicio de conversão para "auto convert"
    AD1CON1bits.CLRASAM = 1;//Determina que o processo de conversão só começa quando é dada a ordem de ínicio de conversão
    AD1CON3bits.SAMC = 16;//Configurar duração do tempo de amostragem (16 = 1600ns)
    AD1CON2bits.SMPI = 3;//Configurar nr de conversão consecutivas do mesmo canal
    AD1CHSbits.CH0SA = 4;//Entrada analógica a converter, canal de entrada (AN6)
    AD1CON1bits.ON = 1;//Ativa conversor A/D
    while(1){
        delay(10);
        if(j++ == 25){
            AD1CON1bits.ASAM = 1;
			while( IFS1bits.AD1IF == 0 );
      
            int *p = (int *)(&ADC1BUF0);
             
            for(i = 0; i < 4; i++){
                soma += p[i*4];
            }

            media = soma/4;
            v = (media*33+511)/1023;
	        v = int2BCD((unsigned int)(v));
        
            soma = 0;
            i = 0;
            IFS1bits.AD1IF=0;//Reset bit
        }
        send2displays(v);
    }
}
