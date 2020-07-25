#include <detpic32.h>
void delay(int);
void displayChar(char);

void main(void){
    LATBbits.LATB15 = 0;
    LATBbits.LATB14 = 0;
    LATBbits.LATB13 = 0;
    LATBbits.LATB12 = 0;
    LATBbits.LATB11 = 0;
    LATBbits.LATB10 = 0;
    LATBbits.LATB9 = 0;
    LATBbits.LATB8 = 0;

    LATDbits.LATD5 = 0;
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
