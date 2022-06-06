#include <REGX52.H>
#include <INTRINS.H>

void Delay1ms();
void Delay1000ms();

// Beep connect to P25
void main()
{
	unsigned int i;
	while(1)
	{
		i = 1000;
		while(i--)
		{
			P2_5 = !P2_5;
			Delay1ms();
		}

		P2_5 = 0;		
		Delay1000ms();
	}
}

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

void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 8;
	j = 1;
	k = 243;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
