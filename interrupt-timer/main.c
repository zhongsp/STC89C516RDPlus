#include <REGX52.H>

sbit LED1 = P2^0;

void init_timer0()
{
	TMOD |= 0x01;
	TH0 = 0xfc;
	TL0 = 0x18;
	ET0 = 1;
	EA = 1;
	TR0 = 1;
}

void timer0_handler() interrupt 1
{
	static unsigned int i;
	TH0 = 0xfc;
	TL0 = 0x18;
	i++;
	if (i == 1000)
	{
		i = 0;
		LED1 = !LED1;
	}
}

void main()
{
	init_timer0();
	
	while(1);
}