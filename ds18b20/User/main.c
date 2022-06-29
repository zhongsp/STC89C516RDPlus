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
#include "ds18b20.h"
#include "smg.h"

gsmg_code[17] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07,
                           0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};
void main()
{
    
//    u8 ack = ds18b20_init();
//    
//    if (ack == 1)
//    {
//        P2_0 = 1;
//    }
//    else
//    {
//        P2_0 = 0;
//    }
//    
//    while (1);
    u8 i = 0;
    int temp_value;
    u8 temp_buf[5];
    
    ds18b20_init();
    
    while (1)
    {
        i++;
        if (i % 50 == 0)
            temp_value = ds18b20_read_temperture()*10;
        
        if (temp_value < 0)
        {
            temp_value = -temp_value;
            temp_buf[0] = 0x40;
        }
        else
        {
            temp_buf[0] = 0x00;
        }
        
        temp_buf[1]=gsmg_code[temp_value/1000];//百位
        temp_buf[2]=gsmg_code[temp_value%1000/100];//十位
        temp_buf[3]=gsmg_code[temp_value%1000%100/10]|0x80;//个位+小数点
        temp_buf[4]=gsmg_code[temp_value%1000%100%10];//小数点后一位
        smg_display(temp_buf,4);
    }
}