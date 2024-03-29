#include "public.h"
#include "iic.h"

/********************************************************************
***********
* 函数名: iic_start
* 函数功能: 产生IIC 起始信号
* 输入: 无
* 输出: 无
*********************************************************************
**********/
void iic_start(void)
{
    IIC_SCL = 1;
    IIC_SDA = 1;
    delay_10us(1);
    IIC_SDA = 0; //当SCL 为高电平时，SDA 由高变为低
    delay_10us(1);
    IIC_SCL = 0; //钳住I2C 总线，准备发送或接收数据
}
/********************************************************************
***********
* 函数名: iic_stop
* 函数功能: 产生IIC 停止信号
* 输入: 无
* 输出: 无
*********************************************************************
**********/
void iic_stop(void)
{
    IIC_SCL = 1;
    IIC_SDA = 0;
    delay_10us(1);
    IIC_SDA = 1; //当SCL 为高电平时，SDA 由低变为高
    delay_10us(1);
}
/********************************************************************
***********
* 函数名: iic_ack
* 函数功能: 产生ACK 应答
* 输入: 无
* 输出: 无
*********************************************************************
**********/
void iic_ack(void)
{
    IIC_SCL = 0;
    IIC_SDA = 0; // SDA 为低电平
    delay_10us(1);
    IIC_SCL = 1;
    delay_10us(1);
    IIC_SCL = 0;
}
/********************************************************************
***********
* 函数名: iic_nack
* 函数功能: 产生NACK 非应答
* 输入: 无
* 输出: 无
*********************************************************************
**********/
void iic_nack(void)
{
    IIC_SCL = 0;
    IIC_SDA = 1; // SDA 为高电平
    delay_10us(1);
    IIC_SCL = 1;
    delay_10us(1);
    IIC_SCL = 0;
}
/********************************************************************
***********
* 函数名: iic_wait_ack
* 函数功能: 等待应答信号到来
* 输入: 无
* 输出: 1，接收应答失败
0，接收应答成功
*********************************************************************
**********/
u8 iic_wait_ack(void)
{
    u8 time_temp = 0;
    IIC_SCL = 1;
    delay_10us(1);
    while (IIC_SDA) //等待SDA 为低电平
    {
        time_temp++;
        if (time_temp > 100) //超时则强制结束IIC 通信
        {
            iic_stop();
            return 1;
        }
    }
    IIC_SCL = 0;
    return 0;
}
/********************************************************************
***********
* 函数名: iic_write_byte
* 函数功能: IIC 发送一个字节
* 输入: dat：发送一个字节
* 输出: 无
*********************************************************************
**********/
void iic_write_byte(u8 dat)
{
    u8 i = 0;
    IIC_SCL = 0;
    for (i = 0; i < 8; i++) //循环8 次将一个字节传出，先传高再传低位
    {
        if ((dat & 0x80) > 0)
            IIC_SDA = 1;
        else
            IIC_SDA = 0;
        dat <<= 1;
        delay_10us(1);
        IIC_SCL = 1;
        delay_10us(1);
        IIC_SCL = 0;
        delay_10us(1);
    }
}
/********************************************************************
***********
285
* 函数名: iic_read_byte
* 函数功能: IIC 读一个字节
* 输入: ack=1 时，发送ACK，ack=0，发送nACK
* 输出: 应答或非应答
*********************************************************************
**********/
u8 iic_read_byte(u8 ack)
{
    u8 i = 0, receive = 0;
    for (i = 0; i < 8; i++) //循环8 次将一个字节读出，先读高再传低位
    {
        IIC_SCL = 0;
        delay_10us(1);
        IIC_SCL = 1;
        receive <<= 1;
        if (IIC_SDA)
            receive++;
        delay_10us(1);
    }
    if (!ack)
        iic_nack();
    else
        iic_ack();
    return receive;
}