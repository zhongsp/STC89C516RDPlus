#ifndef _smg_H
#define _smg_H

#include "public.h"

#define SMG_A_DP_PORT P0 //使用宏定义数码管段码口

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

/********************************************************************
***********
* 函数名: smg_display
* 函数功能: 动态数码管显示
* 输入: dat：要显示的数据
pos：从左开始第几个位置开始显示，范围1-8
* 输出: 无
*********************************************************************
**********/
void smg_display(u8 dat[], u8 pos);

#endif