#include <REGX52.H>
#include <INTRINS.H>

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

unsigned char steps[] = {0x01, 0x03, 0x02, 0x06, 0x04, 0x0c, 0x08, 0x09};

// 1 step == 5.625 / 64 degree
void step(unsigned int n, unsigned char is_rev)
{
	unsigned int i;
	if (is_rev)
	{
		for (i = n; i > 0; i--)
		{
			P1 = steps[i % 8];
			Delay1ms();
		}	
	}
	else
	{
		for (i = 0; i < n; i++)
		{
			P1 = steps[i % 8];
			Delay1ms();
		}	
	}

}

void main()
{
	P1 = 0;
	
	Delay1ms();
 
	step(4096, 1);

	// 电机停止后，让其内部没有电流，否则会持续耗电发热
	P1 = 0;

	while(1);
}