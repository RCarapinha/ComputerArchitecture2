#include <detpic32.h>

volatile unsigned char value2display = 0;

void delay(unsigned int ms){
	for(; ms > 0; ms--){
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}

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

void main(void){
    TRISB &= 0x00FF;
    TRISD &= 0xFF9F;
    //Configurar tudo
    TRISBbits.TRISB4 = 1;//Desliga entrada digital
    AD1PCFGbits.PCFG4 = 0;//Configura como entrada analogica
    AD1CON1bits.SSRC= 7;//Configurar trigger do processo de ínicio de conversão para "auto convert"
    AD1CON1bits.CLRASAM = 1;//Determina que o processo de conversão só começa quando é dada a ordem de ínicio de conversão
    AD1CON3bits.SAMC = 16;//Configurar duração do tempo de amostragem (16 = 1600ns)
    AD1CON2bits.SMPI = 0;//Configurar nr de conversão consecutivas do mesmo canal
    AD1CHSbits.CH0SA = 4;//Entrada analógica a converter, canal de entrada (AN4 -> RB4)
    AD1CON1bits.ON = 1;//Ativa conversor A/D
    //Configurar sistema de interrupçoes
    IPC6bits.AD1IP = 2;//Configurar prioridade
    IEC1bits.AD1IE = 1;//Ativar interrupções A/D
    IFS1bits.AD1IF = 0;//Reset da flag
    EnableInterrupts();//Ativar interrupções globalmente
    int i = 0;
    while(1){
        delay(10);
        if(i++ == 25){
            AD1CON1bits.ASAM = 1;
            i = 0;
        }
        send2displays(value2display);
    }
}

void _int_(27) isr_adc(void){
    //ISR actions
    int *p = (int*)(&ADC1BUF0);
    int j = 0, soma = 0, media, v;
    for(j = 0; j < 8; j++){
        soma += p[j*4];
    }
    media = soma/8;
    v = (media*33+511)/1023;
    value2display = int2BCD(v);
    soma = 0;
    //Começar conversor A/D
    //AD1CON1bits.ASAM = 1;
    IFS1bits.AD1IF = 0;
}
