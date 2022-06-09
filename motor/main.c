#include <REGX52.H>
#include <INTRINS.H>

void Delay1000ms(unsigned char n)		//@11.0592MHz
{
	unsigned char i, j, k;

	while(n)
	{
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
		n--;
	}
	
}

void main()
{
	// 输出高电平、电机进口1输入低电平、电机进口2输入高电平，电机开启
	P1_0 = 1;
	Delay1000ms(3);
	P1_0 = 0;
	while(1);
}