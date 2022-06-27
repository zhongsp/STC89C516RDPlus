#include "public.h"

/********************************************************************
***********
* 函数名: delay_ms
* 函数功能: ms 延时函数，ms=1 时，大约延时1ms
* 输入: ten_us
* 输出: 无
*********************************************************************
**********/
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
