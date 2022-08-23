#ifndef _UART_H
#define _UART_H

void uart_init(void);

void uart_init_115200(void);

void uart_send(unsigned char byte);

#endif
