#include <REGX52.H>

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

unsigned char gsmg_code[17] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

void main()
{
	while(1)
	{
		P1 = 0xf7; // 1111 0111, col 1
		
		// 如果第一列有按键按下，会把高 4 位的 1 拉低为 0。
		if (P1 != 0xf7)
		{
			Delay20ms(); // 消抖

			if (P1_4 == 0)
			{
				while(P1 != 0xf7);
				P0 = gsmg_code[12];
			}
			if (P1_5 == 0)
			{
				while(P1 != 0xf7);
				P0 = gsmg_code[8];
			}
			if (P1_6 == 0)
			{
				while(P1 != 0xf7);
				P0 = gsmg_code[4];
			}
			if (P1_7 == 0)
			{
				while(P1 != 0xf7);
				P0 = gsmg_code[0];
			}
		}
		
		P1 = 0xfb; // 1111 1011, col 2
		
		// 如果第二列有按键按下，会把高 4 位的 1 拉低为 0。
		if (P1 != 0xfb)
		{
			Delay20ms(); // 消抖

			if (P1_4 == 0)
			{
				while(P1 != 0xfb);
				P0 = gsmg_code[13];
			}
			if (P1_5 == 0)
			{
				while(P1 != 0xfb);
				P0 = gsmg_code[9];
			}
			if (P1_6 == 0)
			{
				while(P1 != 0xfb);
				P0 = gsmg_code[5];
			}
			if (P1_7 == 0)
			{
				while(P1 != 0xfb);
				P0 = gsmg_code[1];
			}
		}
		
		P1 = 0xfd; // 1111 1101, col 3
		
		// 如果第三列有按键按下，会把高 4 位的 1 拉低为 0。
		if (P1 != 0xfd)
		{
			Delay20ms(); // 消抖

			if (P1_4 == 0)
			{
				while(P1 != 0xfd);
				P0 = gsmg_code[14];
			}
			if (P1_5 == 0)
			{
				while(P1 != 0xfd);
				P0 = gsmg_code[10];
			}
			if (P1_6 == 0)
			{
				while(P1 != 0xfd);
				P0 = gsmg_code[6];
			}
			if (P1_7 == 0)
			{
				while(P1 != 0xfd);
				P0 = gsmg_code[2];
			}
		}
		
		P1 = 0xfe; // 1111 1110, col 4
		
		// 如果第三列有按键按下，会把高 4 位的 1 拉低为 0。
		if (P1 != 0xfe)
		{
			Delay20ms(); // 消抖

			if (P1_4 == 0)
			{
				while(P1 != 0xfe);
				P0 = gsmg_code[15];
			}
			if (P1_5 == 0)
			{
				while(P1 != 0xfe);
				P0 = gsmg_code[11];
			}
			if (P1_6 == 0)
			{
				while(P1 != 0xfe);
				P0 = gsmg_code[7];
			}
			if (P1_7 == 0)
			{
				while(P1 != 0xfe);
				P0 = gsmg_code[3];
			}
		}
	}
}