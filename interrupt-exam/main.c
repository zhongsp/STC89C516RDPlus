#include <REGX51.H>

void init_int0()
{
    // 开启全局中断
    EA = 1;
    
    // 开启外部中断 0
    EX0 = 1;
    
    // 下降沿触发
    IT0 = 1;
}

void int0_handler() interrupt 0
{
    P2_0 = !P0_0;
    P2_1 = !P0_1;
}

void main()
{
    init_int0();

    while (1);
}
