#include <REGX52.H>

void Delay10us();

sbit LSA = P2^2;
sbit LSB = P2^3;
sbit LSC = P2^4;

unsigned char gsmg_code[17] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

void main()
{
	unsigned char i = 0;
	while(1)
	{
		i = 0;
		for (i = 0; i < 8; i++)
		{
			switch(i)
			{
				case 0: LSC=1;LSB=1;LSA=1;break;
				case 1: LSC=1;LSB=1;LSA=0;break;
				case 2: LSC=1;LSB=0;LSA=1;break;
				case 3: LSC=1;LSB=0;LSA=0;break;
				case 4: LSC=0;LSB=1;LSA=1;break;
				case 5: LSC=0;LSB=1;LSA=0;break;
				case 6: LSC=0;LSB=0;LSA=1;break;
				case 7: LSC=0;LSB=0;LSA=0;break;			
			}
			
			P0 = gsmg_code[i];
			Delay10us(); //延时一段时间，等待显示稳定
			P0 = 0; //消音
		}
	}
}

void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	i = 2;
	while (--i);
}
