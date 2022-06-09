#include <REGX52.H>
#include <INTRINS.H>

sbit SER = P3^4;
sbit RCK = P3^5;
sbit SCK = P3^6;

void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void Delay10us()	//@11.0592MHz
{
	unsigned char i;

	i = 2;
	while (--i);
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

// 工具生成
//unsigned char ghc595_buf[8]={0xF8,0x08,0xF8,0xA8,0x00,0x00,0x00,0x00};
unsigned char ghc595_buf[8]={0x12,0x54,0x38,0xFF,0x38,0x54,0x12,0x00};

unsigned char col_buf[8] = {0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};

void main()
{
	unsigned char i = 0;

	while(1)
	{
		i = 0;
		
		for (i = 0; i < 8; i++)
		{
			P0 = col_buf[i];
			hc595_write_data(ghc595_buf[i]);
			Delay1ms();
			hc595_write_data(0);
		}
	}
}
