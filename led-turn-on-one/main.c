#include <REGX52.H>

// sbit 特殊功能位声明，0 or 1

// D1 euqals P20
sbit D1 = P2^0;
sbit D2 = P2^1;
sbit D3 = P2^2;
sbit D4 = P2^3;
sbit D5 = P2^4;
sbit D6 = P2^5;
sbit D7 = P2^6;
sbit D8 = P2^7;

void main()
{
	// turn on D1
	D1 = 0;
	
	// turn on D3
	D3 = 0;
	
	// turn on D5
	D5 = 0;

	// turn on D7
	D7 = 0;

	while (1);
}
