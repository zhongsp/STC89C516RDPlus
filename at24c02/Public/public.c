#include "public.h"

void delay_ms(u16 ms)		//@11.0592MHz
{
	unsigned char i, j;

    while(ms)
    {
	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
        
        ms--;
    }

}


void delay_10us(u16 us)		//@11.0592MHz
{
	unsigned char i;
    
    while(us)
    {
    	i = 2;
        while (--i);
        
        us--;
    }
}
