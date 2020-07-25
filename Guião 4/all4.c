//Exercicio 2

#include <detpic32.h>
void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);        
    }
}

void main(void){
    LATE &= 0x0;

    TRISE &= 0x0;

    int i = 0;
    
    while(1){
        LATE = i;
        delay(500);
        i = i+1;        
    }
}

//Exercicio 3

#include <detpic32.h>

void main(void){
	LATB &= 0x0000;
	
	TRISB &= 0x000F;
	TRISD &= 0xFF9F;
	
	LATDbits.LATD5 = 0; //Liga Segmento Direita
	LATDbits.LATD6 = 1; //Liga Segmenteo Esquerda
	
	char c;
	while(1){
		printStr("Escreva aqui -> ");
		c = getChar();
		printStr("\n");
		putChar(c);
		printStr("\n");
		switch(c){
			case 'a': 	LATB &= 0x0100; break;
			
			case 'b':  	LATB &= 0x0200; break;
			
			case 'c':  	LATB &= 0x0400; break;
			
			case 'd':  	LATB &= 0x0800; break;
			
			case 'e':  	LATB &= 0x1000; break;
			
			case 'f':  	LATB &= 0x2000; break;
			
			case 'g':  	LATB &= 0x4000; break;
		}
	}
}

//Exercicio 4

#include <detpic32.h>
void delay(int);
void displayChar(int);

void main(void){
    unsigned int segment;
    LATDbits.LATD6 = 1; // display high active
    LATDbits.LATD5 = 0; // display low inactive

    TRISB &= 0x000F;
    
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    
    int i = 0;
    while(1){
        LATDbits.LATD6 = !LATDbits.LATD6; //
        LATDbits.LATD5 = !LATDbits.LATD5; // toggle display selection
        segment = 1;
        for(i=0; i < 7; i++){
            displayChar(segment);// send "segment" value to display
            delay(1000);
            segment = segment + 1;
        }
    }
} 

void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);
    }
}  

void displayChar(int c){
	if(c==1){
		LATB=0x7700;
	}else if(c==2){
		LATB=0x7C00;
	}else if(c==3){
		LATB=0x3900;
	}else if(c==4){
		LATB=0x5E00;
	}else if(c==5){
		LATB=0x7900;
	}else if(c==6){
		LATB=0x7100;
	}else if(c==7){
		LATB=0x7100;
    }
}

//Exercicio 7

#include <detpic32.h>
void delay(int);
void displayChar(char);

void main(void){
    LATB &= 0x0000;

    LATDbits.LATD5 = 0;
    LATDbits.LATD6 = 1;

    TRISB &= 0x000F;
    
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    
    char c;   
    while(1){
	    /*LATDbits.LATD5 = !LATDbits.LATD5;
    	LATDbits.LATD6 = !LATDbits.LATD6;*/

        printf("Escreve: ");
        c = getChar();            
	putChar(c);
	printf("\n");

	displayChar(c);       
    }
}

void displayChar(char c){
	if(c=='A' || c=='a'){
		LATB=0x7700;
	}else if(c=='B' || c=='b'){
		LATB=0x7C00;
	}else if(c=='C' || c=='c'){
		LATB=0x3900;
	}else if(c=='D' || c=='d'){
		LATB=0x5E00;
	}else if(c=='E' || c=='e'){
		LATB=0x7900;
	}else if(c=='F' || c=='f'){
		LATB=0x7100;
	}else if(c=='F' || c=='f'){
		LATB=0x7100;
	}else if(c=='0'){
		LATB=0x3F00;
	}else if(c=='1'){
		LATB=0x0600;
	}else if(c=='2'){
		LATB=0x5B00;
	}else if(c=='3'){
		LATB=0x4F00;
	}else if(c=='4'){
		LATB=0x6600;
	}else if(c=='5'){
		LATB=0x6D00;
	}else if(c=='6'){
		LATB=0x7D00;
	}else if(c=='7'){
		LATB=0x0700;
	}else if(c=='8'){
		LATB=0x7F00;
	}else if(c=='9'){
		LATB=0x6F00;
	}
}  

//Exercicio 9

#include <detpic32.h>
void main(void){
    TRISB = 0x000F;

    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    
    LATDbits.LATD5 = 0;
    LATDbits.LATD6 = 1;

    int a, b, c, d, n;
    static const char display7SCodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};  
    while(1){
        a = PORTBbits.RB0; 
        b = PORTBbits.RB1;
        c = PORTBbits.RB2;
        d = PORTBbits.RB3;       
        n = a+2*b+4*c+8*d;
        LATB = display7SCodes[n]<<8;
    }
}

//Exercicio 10

#include <detpic32.h>
void send2display(int);
void main(void){
    TRISB = 0x000F;

    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 0;

    int a, b, c, d, n = 0;  
    while(1){
        a = PORTBbits.RB0; 
        b = PORTBbits.RB1;
        c = PORTBbits.RB2;
        d = PORTBbits.RB3;       
        n = a+2*b+4*c+8*d;
        send2display(n);
    }
}

void send2display(int value){
    static const char display7SCodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};  
    LATB = display7SCodes[value]<<8;
}

//Exercicio 12

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

void send2displays(int valor){
	static const int display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
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

unsigned char toBcd(unsigned char value){
    return ((value / 10) << 4) + (value % 10);
}

void main(void){
    int a, b, c, d, n = 0;
    unsigned char p; 
    while(1){
        a = PORTBbits.RB0; 
        b = PORTBbits.RB1;
        c = PORTBbits.RB2;
        d = PORTBbits.RB3;       
        n = a+2*b+4*c+8*d;
        send2displays(n);
    }
}
