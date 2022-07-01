#ifndef _key_H
#define _key_H

#include "public.h"

//定义独立按键控制脚
sbit KEY1=P3^1;
sbit KEY2=P3^0;
sbit KEY3=P3^2;
sbit KEY4=P3^3;

//使用宏定义独立按键按下的键值
#define KEY1_PRESS 1
#define KEY2_PRESS 2
#define KEY3_PRESS 3
#define KEY4_PRESS 4
#define KEY_UNPRESS 0

/********************************************************************
***********
* 函数名: key_scan
* 函数功能: 检测独立按键是否按下，按下则返回对应键值
* 输入: mode=0：单次扫描按键
mode=1：连续扫描按键
* 输出: KEY1_PRESS：K1 按下
KEY2_PRESS：K2 按下
KEY3_PRESS：K3 按下
KEY4_PRESS：K4 按下
278
KEY_UNPRESS：未有按键按下
*********************************************************************
**********/
u8 key_scan(u8 mode);

#endif
