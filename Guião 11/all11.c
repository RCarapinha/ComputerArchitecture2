//Exercicio 1.6

#include <detpic32.h>

#define WRITE 0x02
#define RDSR 0x05
#define READ 0x03
#define WRSR 0x01
#define WRDI 0x04
#define WREN 0x06
#define EEPROM_CLOCK 500000

void spi2_setClock(unsigned int clock_freq){
    SPI2BRG = (PBCLK+clock_freq)/(2*clock_freq)-1;
}

void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);    
    }
}

void spi2_init(void){
    volatile char trash;
    SPI2CONbits.ON = 0;
    SPI2CONbits.CKP=0;
	SPI2CONbits.CKE = 1;
    SPI2CONbits.SMP = 0;
	SPI2CONbits.MODE32 = 0;
	SPI2CONbits.MODE16 = 0;
	SPI2CONbits.ENHBUF = 1;
	SPI2CONbits.MSSEN = 1;
	SPI2CONbits.MSTEN = 1;
	while(SPI2STATbits.SPIRBE == 0){
   		trash = SPI2BUF;
	}
	SPI2STATbits.SPIROV = 0;
	SPI2CONbits.ON = 1;
}

char eeprom_readStatus(void){
    volatile char trash;
    while(SPI2STATbits.SPIRBE == 0){
   		trash = SPI2BUF;
	}
    SPI2STATbits.SPIROV = 0;
    SPI2BUF = RDSR;
    SPI2BUF = 0;
    while(SPI2STATbits.SPIBUSY);
    trash = SPI2BUF;
    return SPI2BUF;
}

void eeprom_writeStatusCommand(char command){
    while(eeprom_readStatus()&0x01);
    SPI2BUF = command;
    while(SPI2STATbits.SPIBUSY);
}

int main (void){
    char status;
    spi2_init();
    spi2_setClock(EEPROM_CLOCK);
    while(1){
        status = eeprom_readStatus();
        printInt(status, 2 | 4 << 16);
	printf("\n");
	delay(250);    
    }    
}

//Exercicio 1.9

#include <detpic32.h>

#define WRITE 0x02
#define RDSR 0x05
#define READ 0x03
#define WRSR 0x01
#define WRDI 0x04
#define WREN 0x06
#define EEPROM_CLOCK 500000

void spi2_setClock(unsigned int clock_freq){
    SPI2BRG = (PBCLK+clock_freq)/(2*clock_freq)-1;
}

void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);    
    }
}

void spi2_init(void){
    volatile char trash;
    SPI2CONbits.ON = 0;
    SPI2CONbits.CKP=0;
	SPI2CONbits.CKE = 1;
    SPI2CONbits.SMP = 0;
	SPI2CONbits.MODE32 = 0;
	SPI2CONbits.MODE16 = 0;
	SPI2CONbits.ENHBUF = 1;
	SPI2CONbits.MSSEN = 1;
	SPI2CONbits.MSTEN = 1;
	while(SPI2STATbits.SPIRBE == 0){
   		trash = SPI2BUF;
	}
	SPI2STATbits.SPIROV = 0;
	SPI2CONbits.ON = 1;
}

char eeprom_readStatus(void){
    volatile char trash;
    while(SPI2STATbits.SPIRBE == 0){
   		trash = SPI2BUF;
	}
    SPI2STATbits.SPIROV = 0;
    SPI2BUF = RDSR;
    SPI2BUF = 0;
    while(SPI2STATbits.SPIBUSY);
    trash = SPI2BUF;
    return SPI2BUF;
}

void eeprom_writeStatusCommand(char command){
    while(eeprom_readStatus()&0x01);
    SPI2BUF = command;
    while(SPI2STATbits.SPIBUSY);
}

void eeprom_writeData(int address, char value){
    address = address & 0x1FF;
    while(eeprom_readStatus() & 0x01);
    eeprom_writeStatusCommand(WREN);
    SPI2BUF = WRITE | ((address & 0x100) >> 5);
    SPI2BUF = address;
    SPI2BUF = value;
    while(SPI2STATbits.SPIBUSY);
}

char eeprom_readData(int address){
    volatile char trash;
    while(SPI2STATbits.SPIRBE == 0){
   		trash = SPI2BUF;
	}
	SPI2STATbits.SPIROV = 0;
    address = address & 0x1FF;
    while(eeprom_readStatus() & 0x01);
    SPI2BUF = READ | ((address & 0x100) >> 5);
    SPI2BUF = address;
    SPI2BUF = 0x00;
    while(SPI2STATbits.SPIBUSY);
    trash = SPI2BUF;
	trash = SPI2BUF;
    return SPI2BUF;
}

int main (void){
    char status;
    spi2_init();
    spi2_setClock(EEPROM_CLOCK);
    eeprom_writeStatusCommand(WREN);
    while(1){
        status = eeprom_readStatus();
        printInt(status, 2 | 4 << 16);
	printf("\n");
	delay(250);    
    }    
}

//Exercicio 1.10

#include <detpic32.h>

#define WRITE 0x02
#define RDSR 0x05
#define READ 0x03
#define WRSR 0x01
#define WRDI 0x04
#define WREN 0x06
#define EEPROM_CLOCK 500000

void spi2_setClock(unsigned int clock_freq){
    SPI2BRG = (PBCLK+clock_freq)/(2*clock_freq)-1;
}

void delay(int ms){
    for(; ms > 0; ms--){
        resetCoreTimer();
        while(readCoreTimer() < 20000);    
    }
}

void spi2_init(void){
    volatile char trash;
    SPI2CONbits.ON = 0;
    SPI2CONbits.CKP=0;
	SPI2CONbits.CKE = 1;
    SPI2CONbits.SMP = 0;
	SPI2CONbits.MODE32 = 0;
	SPI2CONbits.MODE16 = 0;
	SPI2CONbits.ENHBUF = 1;
	SPI2CONbits.MSSEN = 1;
	SPI2CONbits.MSTEN = 1;
	while(SPI2STATbits.SPIRBE == 0){
   		trash = SPI2BUF;
	}
	SPI2STATbits.SPIROV = 0;
	SPI2CONbits.ON = 1;
}

char eeprom_readStatus(void){
    volatile char trash;
    while(SPI2STATbits.SPIRBE == 0){
   		trash = SPI2BUF;
	}
    SPI2STATbits.SPIROV = 0;
    SPI2BUF = RDSR;
    SPI2BUF = 0;
    while(SPI2STATbits.SPIBUSY);
    trash = SPI2BUF;
    return SPI2BUF;
}

void eeprom_writeStatusCommand(char command){
    while(eeprom_readStatus()&0x01);
    SPI2BUF = command;
    while(SPI2STATbits.SPIBUSY);
}

void eeprom_writeData(int address, char value){
    address = address & 0x1FF;
    while(eeprom_readStatus() & 0x01);
    eeprom_writeStatusCommand(WREN);
    SPI2BUF = WRITE | ((address & 0x100) >> 5);
    SPI2BUF = address;
    SPI2BUF = value;
    while(SPI2STATbits.SPIBUSY);
}

char eeprom_readData(int address){
    volatile char trash;
    while(SPI2STATbits.SPIRBE == 0){
   		trash = SPI2BUF;
	}
	SPI2STATbits.SPIROV = 0;
    address = address & 0x1FF;
    while(eeprom_readStatus() & 0x01);
    SPI2BUF = READ | ((address & 0x100) >> 5);
    SPI2BUF = address;
    SPI2BUF = 0x00;
    while(SPI2STATbits.SPIBUSY);
    trash = SPI2BUF;
	trash = SPI2BUF;
    return SPI2BUF;
}

int main (void){
    char option, value;
    int address;
    spi2_init();
    spi2_setClock(EEPROM_CLOCK);
    eeprom_writeStatusCommand(WREN);
    while(1){
        printf("\nR/W -> ");
        option = getChar();
        
        if(option == 'R' || option == 'r'){
            printf("\nAddress -> ");
            address = readInt10();
            printf("\nValue -> ");
            putChar(eeprom_readData(address));
        }

        else if(option == 'W' || option == 'w'){
	    printf("\n");
            printf("Address -> ");
            address = readInt10();
            printf("\nValue -> ");
            value = getChar();
	    printf("%c", value);
            eeprom_writeData(address, value);    
        }
	printf("\n");
    }
}
