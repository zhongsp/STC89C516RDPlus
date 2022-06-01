#include <INTRINS.H>
#include <REGX52.H>

sbit D1 = P2^0;

void Delay500ms()		//@11.0592MHz
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

void main()
{
	while (1)
	{
		D1 = 0;
		Delay500ms();
		D1= 1;
		Delay500ms();
	}
}