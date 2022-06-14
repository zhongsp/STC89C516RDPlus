#include <REGX52.H>

sbit LED1 = P2^0;

sbit KEY3 = P3^2;
sbit KEY4 = P3^3;

void Delay20ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 36;
	j = 217;
	do
	{
		while (--j);
	} while (--i);
}

void exint0() interrupt 0
{
	Delay20ms();
	
	if (KEY3 == 0)
	{
		LED1 = !LED1;
	}
}

void exint1() interrupt 2
{
	Delay20ms();
	
	if (KEY4 == 0)
	{
		LED1 = !LED1;
	}
}

void enable_ext0_interrupt()
{
	// 下降沿触发
	IT0 = 1;
	
	// 允许外部中断0
	EX0 = 1;
	
	// 允许CPU中断
	EA = 1;
}

void enable_ext1_interrupt()
{
	// 下降沿触发
	IT1 = 1;
	
	// 允许外部中断0
	EX1 = 1;
	
	// 允许CPU中断
	EA = 1;
}

void main()
{
	enable_ext0_interrupt();
	enable_ext1_interrupt();

	while(1);
}