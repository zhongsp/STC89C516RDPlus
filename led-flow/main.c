#include <INTRINS.H>
#include <REGX52.H>

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
	unsigned char i;
	while(1)
	{
		for (i = 0; i < 8; i++)
		{
			P2 = ~(1 << i);
			Delay500ms();
		}
	}
}