#include <REGX52.H>
#include <INTRINS.H>

sbit SER = P3^4;
sbit RCK = P3^5;
sbit SCK = P3^6;

void Delay10us()	//@11.0592MHz
{
	unsigned char i;

	i = 2;
	while (--i);
}

void Delay500ms()	//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 4;
	j = 129;
	k = 119;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void tick()
{
	SCK = 0;
	Delay10us();
	SCK = 1;
	Delay10us();
}

void hc595_write_data(unsigned char dat)
{
	unsigned char i = 0;
	for (i = 0; i < 8; i++)
	{
		SER = dat >> 7;
		dat <<= 1;
		tick();
	}
	RCK = 0;
	Delay10us();
	RCK = 1;
	Delay10us();
}

unsigned char ghc595_buf[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

void main()
{
	unsigned char i = 0;

	while(1)
	{
		i = 0;
		
		P0 = 0;
		for (i = 0; i < 8; i++)
		{
			hc595_write_data(0);
			hc595_write_data(ghc595_buf[i]);
			Delay500ms();
		}
	}
}
