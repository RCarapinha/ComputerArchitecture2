#include <detpic32.h>

#define WRITE 0x02
#define RDSR 0x05
#define READ 0x03
#define WRSR 0x01
#define WRDI 0x04
#define WREN 0x06
#define EEPROM_CLOCK 500000

#define I2C_READ 1
#define I2C_WRITE 0
#define I2C_ACK 0
#define I2C_NACK 1

#define SENS_ADDRESS 0x4D
#define ADDR_WR ((SENS_ADDRESS << 1)| I2C_WRITE)
#define ADDR_RD ((SENS_ADDRESS << 1)| I2C_READ)
#define TC74_CLK_FREQ 100000
#define RTR 0

void i2c1_init(unsigned int clock_freq){
    I2C1BRG=(PBCLK+clock_freq)/(2*clock_freq)-1;
    I2C1CONbits.ON = 1;
}

void i2c1_start(void){
    I2C1CONbits.SEN = 1;
    while(I2C1CONbits.SEN == 1);
}

void i2c1_stop(void){
    while((I2C1CON & 0x1F) != 0); 
    I2C1CONbits.PEN = 1;
    while(I2C1CONbits.PEN == 1);
}

int i2c1_send(unsigned char value){
    I2C1TRN = value; 
    while(I2C1STATbits.TRSTAT == 1);
    return I2C1STATbits.ACKSTAT; 
}

char i2c1_receive(char ack_bit){
    while((I2C1CON & 0x1F) != 0);
    I2C1CONbits.RCEN = 1;
    while(I2C1STATbits.RBF == 0);
    
    if(ack_bit == 0 || ack_bit == 1){
        I2C1CONbits.ACKDT = ack_bit;
    }
    else{
        return 0;
    }
    
    while((I2C1CON & 0x1F) != 0);
    I2C1CONbits.ACKEN = 1;

    while(I2C1CONbits.ACKEN);
    return I2C1RCV;
}

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
    int ack, temperature;
    i2c1_init(TC74_CLK_FREQ);
    char option, value;
    int address = 0x002, count = 0;
    spi2_init();
    spi2_setClock(EEPROM_CLOCK);
    eeprom_writeStatusCommand(WREN);    
    while(1){
        i2c1_start();
        ack = i2c1_send(ADDR_WR);
        ack = ack + i2c1_send(RTR);
        i2c1_start();
        ack = ack + i2c1_send(ADDR_RD);
        if(ack != 0){
            i2c1_stop();
            printf("Error\n");
            break;        
        }
        temperature = i2c1_receive(I2C_NACK);
	i2c1_stop();
	printStr("Temperatura -> ");
        printInt10(temperature);
	printf("\n");
        delay(250);
	printStr("Option -> ");
	option = getChar();
	printStr("\n");
	
	if(option == 'R'){
		eeprom_writeData(0x000,0);
	}
	else if(option == 'L'){
		count++;
		eeprom_writeData(address, temperature); 
		eeprom_writeData(0x000, count);		
		if(address == 0x64){
			printStr("Mem Full");		
		}
		else{
			address &= 0x001;
		}
	}
    }
}
