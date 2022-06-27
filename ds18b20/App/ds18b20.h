#ifndef _ds18b20_H
#define _ds18b20_H

#include "public.h"

sbit DS18B20_PORT = P3^7;

u8 ds18b20_init(void);
void ds18b20_reset(void);
u8 ds18b20_check(void);
float ds18b20_read_temperture(void);
void ds18b20_start(void);
void ds18b20_write_byte(u8 dat);
u8 ds18b20_read_byte(void);

#endif
