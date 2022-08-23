#include <REGX52.H>
#include <INTRINS.H>
#include "lcd1602.h"
#include "uart.h"

char response[8];
unsigned char j = 0;

void uart() interrupt 4
{
    unsigned char rec;

    if (RI == 1)
    {
        RI = 0;

        rec = SBUF;
        if (rec != '\r' && rec != '\n')
        {
            uart_send(rec);
            response[j] = rec;
            j++;
            
        }
        
        if (rec == '\0')
        {
            LCD_WriteCommand(0x01);
            LCD_ShowString(1, 1, response);
        }
    }
}

// AT+CIOBAUD=9600
// 设置 ESP8266 BAUD 为 9600
void main()
{
    char cmd[] = "AT\r\n";
    int i;

    LCD_Init();

    uart_init();

    for (i = 0; i < 4; i++)
    {
        uart_send(cmd[i]);
    }

    while (1);
}
