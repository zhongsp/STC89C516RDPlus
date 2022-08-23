#include <REGX52.H>
#include "uart.h"

void uart() interrupt 4
{
    unsigned char rec_data;

    // 必须软件置 0
    RI = 0;
    
    // 读取接收到的数据
    rec_data = SBUF;
    
    // 写待发送数据，单片机自动发送
    SBUF = rec_data;
    while (!TI)
        ;
    TI = 0;
}

void main()
{
    uart_init(0xfa);
    while (1)
        ;
}
