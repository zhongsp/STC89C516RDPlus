/********************************************************************
******************
实验名称：I2C-EEPROM 实验
接线说明：
实验现象：下载程序后，数码管右4 位显示0，按K1 键将数据写入到EEPROM 内保存，
按K2 键读取EEPROM 内保存的数据，按K3 键显示数据加1，按K4 键显示数据清
零，
最大能写入的数据是255。
注意事项：
*********************************************************************
******************/

#include "public.h"
#include "smg.h"

sbit IRED = P3^2;

gsmg_code[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
                           0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};

u8 gired_data[4];
                           
void init_ired()
{
    IT0 = 1;
    EX0 = 1;
    EA = 1;
    IRED = 1;
}

void ired() interrupt 0
{
    u8 ired_high_time = 0;
    u16 time_cnt = 0;
    u8 i = 0, j = 0;
        
    if (IRED == 0)
    {
        time_cnt = 1000;
        while((!IRED) && time_cnt)
        {
            delay_10us(1);
            time_cnt--;
            if (time_cnt == 0) return ;
        }
        if (IRED)
        {
            time_cnt = 500;
            while (IRED && time_cnt)
            {
                delay_10us(1);
                time_cnt--;
                if (time_cnt == 0) return;
            }
            for (i = 0; i < 4; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    time_cnt = 600;
                    while ((IRED == 0) && time_cnt)
                    {
                        delay_10us(1);
                        time_cnt--;
                        if (time_cnt == 0) return;
                    }
                    time_cnt = 20;
                    while (IRED)
                    {
                        delay_10us(10);
                        ired_high_time++;
                        if (ired_high_time > 20) return;
                    }
                    gired_data[i] >>= 1;
                    if (ired_high_time >= 8) gired_data[i] |= 0x80;
                    ired_high_time = 0;
                }
            }
        }
        
        if (gired_data[2] != ~gired_data[3])
        {
            for (i = 0; i < 4; i++)
            {
                gired_data[i] = 0;
            }
            return ;
        }
        
        // 控制直流电机
        if (gired_data[2] == 0x45)
        {
            P1_0 = ~P1_0;
        }
    }
}

void main()
{
    u8 ired_buf[3];
    init_ired();
    
    P1_0 = 0;
    
    while (1)
    {
        ired_buf[0] = gsmg_code[gired_data[2] / 16];
        ired_buf[1] = gsmg_code[gired_data[2] % 16];
        ired_buf[2] = 0x76;
               
        smg_display(ired_buf, 6);
    }
}
