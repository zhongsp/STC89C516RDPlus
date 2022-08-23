#include <REGX52.H>

sfr AUXR    = 0x8E;

void uart_init(void) //9600bps@11.0592MHz
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
    TH1 = 0xFA;
    TL1 = 0xFA;

    ES = 1;
    EA = 1;
    TR1 = 1;
}

void uart_init_115200(void)		//115200bps@11.0592MHz
{
	SCON = 0x50;		//8bit and variable baudrate
	AUXR &= 0xBF;		//Timer1's clock is Fosc/12 (12T)
	AUXR &= 0xFE;		//Use Timer1 as baudrate generator
	TMOD &= 0x0F;		//Set Timer1 as 16-bit auto reload mode
	TL1 = 0xFE;		//Initial timer value
	TH1 = 0xFF;		//Initial timer value
	ET1 = 0;		//Disable Timer1 interrupt
	TR1 = 1;		//Timer1 running
    
    ES = 1;
    EA = 1;
}


void uart_send(unsigned char byte)
{
    SBUF = byte;
    // 等待 TI 变为 1，即发送完成
    while (!TI);
    TI = 0;
}
