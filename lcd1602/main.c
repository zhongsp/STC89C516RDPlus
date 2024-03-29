#include <REGX52.H>

void uart_init(unsigned char baud)
{
    // 定时器工作方式寄存器，复位后为0
    //
    // GATE C/T M1 M0 GATE C/T M1 M0
    // 定时器1          定时器0
    //
    // 定时器 1 工作方式设置为 2，即自动重装初值的8 位计数方式
    TMOD |= 0x20; // 00100000
    
    // 设置串口工作方式 1，方式1 是10 位数据的异步通信口，数据 8 位
    //
    // SM0 SM1 SM2 REN TB8 RB8 TI RI
    // 复位后为 0
    SCON = 0x50; // 01010000
    
    // SMOD = 1，波特率加倍
    PCON = 0x80; // 10000000
    
    // 设置计数器初始值
    // 串口工作模式 1 使用 Timer 1 来设置波特率，产生时钟
    // = (2^SMOD / 32) * T1溢出率
    // T1溢出率 = fosc / 12 / (256 - TH1)
    // 12 为单片机使用 12 个时钟作为一个机器周期
    TH1 = baud;
    TL1 = baud;

    ES = 1;
    EA = 1;
    TR1 = 1;
}

void uart() interrupt 4
{
    char cmd[] = { 'A', 'T', '+', 'V', 'E', 'R','S','I', 'O', 'N', '\r', '\n', '\0' };
    int i;
    
    char rec[] = "x";
    if (RI == 1)
    {
        // 必须软件置 0
        RI = 0;
        
        // 读取接收到的数据
        rec[0] = SBUF;
        LCD_ShowString(2,1,"J");//第二行显示
    }
    
    if (TI == 1)
    {
        TI = 0;
        
        for (i = 0; i < 13; i++)
        {
            SBUF = cmd[i];
            while (!TI);
            TI = 0;
        }
    }
}

void main()
{
    uart_init(0xfa);
    
    LCD_Init();//LCD1602 初始化
    LCD_ShowString(1,1,"Hello World!");//第一行显示
    LCD_ShowString(2,1,"0123456789");//第二行显示

    SBUF = ' ';

    while(1)
    {
    }
}