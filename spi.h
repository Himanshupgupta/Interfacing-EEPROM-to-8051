//pin connections
extern bit SCLK;
extern bit MOSI;
extern bit MISO;
extern bit SS;


void SPI_Write(unsigned char Data)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		//SCLK=1;
		if(Data & 0x80)
			MOSI=1;
		else
			MOSI=0;
		SCLK=1;
		Data<<=1;
		SCLK=0;
	}
}

unsigned char SPI_Read()
{
	unsigned char i,Data;
	for(i=0;i<8;i++)
	{
		SCLK=1;
		Data<<=1;
		if(MISO)
			Data|=MISO;
		SCLK=0;
	}
	return Data;
}