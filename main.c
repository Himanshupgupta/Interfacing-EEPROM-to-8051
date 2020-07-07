#include<reg51.h>
#include"spi.h"

//pin connections
sbit SCLK=P2^0;
sbit MOSI=P2^1;
sbit MISO=P2^2;
sbit SS=P2^3;

unsigned char EEP_Read_Byte(unsigned char Address)
{
	unsigned char Data;
	SS=0;
	SPI_Write(0x04);   //Disable WREN 
	SS=1;
	
	SS=0;
	SPI_Write(0x03);
	SPI_Write(Address>>8);
	SPI_Write(Address & 0x00FF);
	Data=SPI_Read();
	SS=1;
	return Data;
}

//EEP_Read_Bytes()

void EEP_Write_Byte(unsigned char Address,unsigned char Data)
{
	SS=0;
	SPI_Write(0x06);  //send the WREN 
	SS=1;
	
	SS=0;
	SPI_Write(0x02);
	SPI_Write(Address>>8);
	SPI_Write(Address & 0x00FF);
	SPI_Write(Data);
	SS=1;
	//while(EEP_Check_Status());
}

void EEP_Write_Bytes(unsigned char Address,unsigned char Data)
{
	SS=0;
	SPI_Write(0x06);                 //send the WREN 
	SS=1;
	
	SS=0;
	SPI_Write(0x02);                 //Write to EEPROM
	SPI_Write(Address>>8);
	SPI_Write(Address & 0x00FF);
	SPI_Write('a');
	SPI_Write('b');
	SS=1;
}

EEP_Check_Status()
{
	unsigned char b;
	SS=0;
	SPI_Write(0x05);
	b=SPI_Read();
	SS=1;
	if(b&0x01)
		return 1;
	else
		return 0;
}

void delay(int ms)
{
	int i,j;
	for(i=0;i<ms;i++)
	for(j=0;j<1275;j++);
}

void main()
{
	unsigned char Name='a';
	EEP_Write_Bytes(0x0000,Name);
	//delay(10000);
	EEP_Read_Byte(0x0002);
	while(1);
}