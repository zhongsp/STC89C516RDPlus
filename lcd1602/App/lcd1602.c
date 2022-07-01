
sbit LCD1602_RS = P2^6;
sbit LCD1602_RW = P2^5;
sbit LCD1602_E = P2^7;

#define LCD1602_DATAPORT P0

void delay_1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void lcd1602_write_cmd(u8 cmd)
{
    LCD1602_RS=0;//选择命令
    LCD1602_RW=0;//选择写
    LCD1602_E=0;
    LCD1602_DATAPORT=cmd;//准备命令
    delay_1ms();
    LCD1602_E=1;//使能脚E 先上升沿写入
    delay_1ms();
    LCD1602_E=0;//使能脚E 后负跳变完成写入
}

void lcd1602_write_data(u8 dat)
{
    LCD1602_RS=1;//选择数据
    LCD1602_RW=0;//选择写
    LCD1602_E=0;
    LCD1602_DATAPORT=dat;//准备数据
    delay_1ms();
    LCD1602_E=1;//使能脚E 先上升沿写入
    delay_1ms();
    LCD1602_E=0;//使能脚E 后负跳变完成写入
}

void lcd1602_init(void)
{
    lcd1602_write_cmd(0x38);//数据总线8 位，显示2 行，5*7 点阵/字符
    lcd1602_write_cmd(0x0c);//显示功能开，无光标，光标闪烁
    lcd1602_write_cmd(0x06);//写入新数据后光标右移，显示屏不移动
    lcd1602_write_cmd(0x01);//清屏
}

void lcd1602_clear(void)
{
    lcd1602_write_cmd(0x01);
}

void lcd1602_show_string(u8 x,u8 y,u8 *str)
{
    u8 i=0;
    if(y>1||x>15)return;//行列参数不对则强制退出
    if(y<1) //第1 行显示
    {
        while(*str!='\0')//字符串是以'\0'结尾，只要前面有内容就显示
        {
            if(i<16-x)//如果字符长度超过第一行显示范围，则在第二行继续显示
            {
                lcd1602_write_cmd(0x80+i+x);//第一行显示地址设置
            }
            else
            {
                lcd1602_write_cmd(0x40+0x80+i+x-16);//第二行显示地址设置
            }
            lcd1602_write_data(*str);//显示内容
            str++;//指针递增
            i++;
        }
    }
    else //第2 行显示
    {
    while(*str!='\0')
    {
        if(i<16-x) //如果字符长度超过第二行显示范围，则在第一行继续显示
        {
            lcd1602_write_cmd(0x80+0x40+i+x);
        }
        else
        {
            lcd1602_write_cmd(0x80+i+x-16);
        }
            lcd1602_write_data(*str);
            str++;
            i++;
        }
    }
}