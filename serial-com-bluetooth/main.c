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

void main()
{
    uart_init(0xfa);
    while (1)
        ;
}

sbit LED0 = P2^0;
sbit LED1 = P2^1;
sbit LED2 = P2^2;
sbit LED3 = P2^3;

void uart() interrupt 4
{
    unsigned char rec_data;

    // 必须软件置 0
    RI = 0;
    
    // 读取接收到的数据
    rec_data = SBUF;
    
    if (rec_data == '0')
    {
        LED0 = !LED0;
    }
    if (rec_data == '1')
    {
        LED1 = !LED1;
    }
    if (rec_data == '2')
    {
        LED2 = !LED2;
    }
    if (rec_data == '3')
    {
        LED3 = !LED3;
    }
    
    // 写待发送数据，单片机自动发送
//    SBUF = rec_data;
//    while (!TI)
//        ;
//    TI = 0;
}
