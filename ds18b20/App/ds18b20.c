#include "ds18b20.h"

u8 ds18b20_init(void)
{
ds18b20_reset();
return ds18b20_check();
}

void ds18b20_reset(void)
{
    // 主机输出低电平
    DS18B20_PORT = 0;
    
    // 保持低电平 480-960us
    delay_10us(75);
    
    // 主机释放总线，上拉电阻将总线拉高电平
    DS18B20_PORT = 1;
    
    // 操持高电平 15 - 60us
    delay_10us(2);
}

u8 ds18b20_check(void)
{
    u8 time_temp = 0;
    
    // 如果有 ds18b20 器件，在复位后，它会产生一个低电平
    while (DS18B20_PORT && time_temp < 20)
    {
        time_temp++;
        delay_10us(1);
    }
    
    if (time_temp >= 20)
        return 1;
    else
        time_temp = 0;
    
    while ((!DS18B20_PORT) && time_temp < 20)
    {
        time_temp++;
        delay_10us(1);
    }
    if (time_temp >= 20) return 1;
    return 0;
}

float ds18b20_read_temperture(void)
{
    float temp;
    u8 dath = 0;
    u8 datl = 0;
    u16 value = 0;
    
    ds18b20_start();
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
    return temp;
}

void ds18b20_start(void)
{
    ds18b20_reset();
    ds18b20_check();
    ds18b20_write_byte(0xcc);
    ds18b20_write_byte(0x44);
}

void ds18b20_write_byte(u8 dat)
{
    u8 i = 0;
    for (i = 0; i < 8; i++)
    {
        if ((dat & 0x80) > 0)
        {
            // write 1
            DS18B20_PORT = 0;
            delay_2us();
            DS18B20_PORT = 1;
            delay_10us(6);
        }
        else
        {
            // write 0
            DS18B20_PORT = 0;
            delay_10us(6);
            DS18B20_PORT = 1;
            delay_2us();
        }
        
        dat<<=1;
    }
}

u8 ds18b20_read_byte(void)
{
    u8 dat = 0;
    u8 i = 0;
    u8 value = 0;
    
    for (i = 0; i< 8; i++)
    {
        DS18B20_PORT = 0;
        delay_2us();
        DS18B20_PORT = 1;
        delay_10us(1);
        delay_2us();
        value = DS18B20_PORT;
        if (DS18B20_PORT == 0)
        {
            dat >>= 1;
        }
        else
        {
            dat >>= 1;
            dat |= 0x80;
        }
        delay_10us(5);
    }
    
    return dat;
}


