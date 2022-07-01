#include "smg.h"

/********************************************************************
***********
* 函数名: smg_display
* 函数功能: 动态数码管显示
* 输入: dat：要显示的数据
pos：从左开始第几个位置开始显示，范围1-8
* 输出: 无
*********************************************************************
**********/
void smg_display(u8 dat[], u8 pos)
{
    u8 i = 0;
    u8 pos_temp = pos - 1;
    for (i = pos_temp; i < 8; i++)
    {
        switch (i) //位选
        {
        case 0:
            LSC = 1;
            LSB = 1;
            LSA = 1;
            break;
        case 1:
            LSC = 1;
            LSB = 1;
            LSA = 0;
            break;
        case 2:
            LSC = 1;
            LSB = 0;
            LSA = 1;
            break;
        case 3:
            LSC = 1;
            LSB = 0;
            LSA = 0;
            break;
        case 4:
            LSC = 0;
            LSB = 1;
            LSA = 1;
            break;
        case 5:
            LSC = 0;
            LSB = 1;
            LSA = 0;
            break;
        case 6:
            LSC = 0;
            LSB = 0;
            LSA = 1;
            break;
        case 7:
            LSC = 0;
            LSB = 0;
            LSA = 0;
            break;
        }
        SMG_A_DP_PORT = dat[i - pos_temp]; //传送段选数据
        delay_10us(100);                              //延时一段时间，等待显示稳定
        SMG_A_DP_PORT = 0x00;                         //消音
    }
}