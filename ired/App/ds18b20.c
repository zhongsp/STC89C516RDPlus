#include "ds18b20.h"

u8 ds18b20_init(void)
{
    ds18b20_reset();
    return ds18b20_check();
}
void Delay5us()		//@11.0592MHz
{
}
void Delay50us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 20;
	while (--i);
}

void Delay700us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 61;
	do
	{
		while (--j);
	} while (--i);
}

void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	i = 2;
	while (--i);
}


void ds18b20_reset(void)
{
    // 主机输出低电平
    DS18B20_PORT = 0;
    
    // 保持低电平 480-960us
    Delay700us();
    
    // 主机释放总线，上拉电阻将总线拉高电平
    DS18B20_PORT = 1;
    
    // 操持高电平 15 - 60us
    Delay50us();
}

u8 ds18b20_check(void)
{
    u8 time_temp = 0;
    
    // 如果有 ds18b20 器件，在复位后，它会产生一个低电平
    while (DS18B20_PORT && time_temp < 20)
    {
        time_temp++;
        Delay10us();
    }
    
    if (time_temp >= 20)
        return 1;
    else
        time_temp = 0;
    
    while ((!DS18B20_PORT) && time_temp < 20)
    {
        time_temp++;
        Delay10us();
    }
    if (time_temp >= 20) return 1;
    
    Delay700us();

    return 0;
}

float ds18b20_read_temperture(void)
{
    float temp;
    u8 dath = 0;
    u8 datl = 0;
    u16 value = 0;
    
    ds18b20_start();
    Delay700us();
    ds18b20_reset();
    ds18b20_check();
    
    // skip rom
    ds18b20_write_byte(0xcc);
    
    // read memory
    ds18b20_write_byte(0xbe);
    
    datl=ds18b20_read_byte();
    dath=ds18b20_read_byte();
    value = (dath<<8)+datl;
    
    if ((value & 0xf800) == 0xf800)
    {
        value = (~value) + 1;
        temp = value * 0.0625;
    }
    else
    {
        temp = value * 0.0625;
    }
    return temp;
}

void ds18b20_start(void)
{
    ds18b20_reset();
    ds18b20_check();
    ds18b20_write_byte(0xcc);
    ds18b20_write_byte(0x44);
}

void write_bit(u8 b)
{
    DS18B20_PORT = 0;
    Delay10us();
    DS18B20_PORT = b;
    Delay50us();
    DS18B20_PORT = 1;
}

u8 read_bit()
{
    u8 i;
    u8 Bit;
    DS18B20_PORT = 0;
    Delay5us();
    DS18B20_PORT = 1;
    Delay5us();
    Bit = DS18B20_PORT;
    Delay50us();
    return Bit;
}

void ds18b20_write_byte(u8 dat)
{
    u8 i = 0;
    u8 j = 0;

    for (i = 0; i < 8; i++)
    {
        if ((dat & 0x01) > 0)
        {
            // write 1
            DS18B20_PORT = 0;
            _nop_();
            DS18B20_PORT = 1;
            // 60us
            j = 27;
            while (--j);
        }
        else
        {
            // write 0
            DS18B20_PORT = 0;

            // 60us
            j = 27;
            while (--j);

            DS18B20_PORT = 1;
            
            // 2us
            _nop_();
        }
        
        dat>>=1;
        _nop_();
    }
}

u8 ds18b20_read_byte(void)
{
    u8 dat = 0;
    u8 i = 0;
    u8 value = 0;
    
    u8 j = 0;
    
    for (i = 0; i< 8; i++)
    {
        DS18B20_PORT = 0;
        _nop_(); // 2us
        DS18B20_PORT = 1;

        // 12us
        j = 3;
        while (--j);

        value = DS18B20_PORT;
        Delay50us();

        if (value == 0)
        {
            dat >>= 1;
        }
        else
        {
            dat >>= 1;
            dat |= 0x80;
        }
        
        _nop_();
    }
    
    return dat;
}
