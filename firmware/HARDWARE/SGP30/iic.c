#include "iic.h"
#include "delay.h"
 
 
 
//开启时钟
static void I2C_CKCU_Config()
{
	CKCU_PeripClockConfig_TypeDef CCLOCK;
	
	CCLOCK.Bit.PA     = 1;
	CCLOCK.Bit.AFIO  = 1;
	
	CKCU_PeripClockConfig(CCLOCK, ENABLE);
}
 
//引脚配置
static void I2C_GPIO_Config()
{
	AFIO_GPxConfig(I2C_SCL_GPIO_ID, I2C_SCL_PIN, I2C_SCL_AFIO_MODE);
	AFIO_GPxConfig(I2C_SDA_GPIO_ID, I2C_SDA_PIN, I2C_SDA_AFIO_MODE);
	
	/* Configure the GPIO pin                                                                                 */
	GPIO_PullResistorConfig(I2C_SCL_PORT, I2C_SCL_PIN, GPIO_PR_DISABLE);
	GPIO_DriveConfig(I2C_SCL_PORT, I2C_SCL_PIN, GPIO_DV_8MA);
	GPIO_DirectionConfig(I2C_SCL_PORT, I2C_SCL_PIN, GPIO_DIR_OUT);
	
	GPIO_PullResistorConfig(I2C_SDA_PORT, I2C_SDA_PIN, GPIO_PR_DISABLE);
	GPIO_DriveConfig(I2C_SDA_PORT, I2C_SDA_PIN, GPIO_DV_8MA);
	GPIO_DirectionConfig(I2C_SDA_PORT, I2C_SDA_PIN, GPIO_DIR_OUT);
}
//初始化 
void I2C_Initia()
{
	I2C_CKCU_Config();
	I2C_GPIO_Config();
	
	/* 一定要先发一遍停止信号 */
	I2C_Stop();
}
 
//I2C起始信号
void I2C_Start()
{
	
	I2C_SDA_InputConfig();
	I2C_SDA_Direction_Output(); //sda线输出
	I2C_SDA_1();
	I2C_SCL_1();
	
	delay_us(4);
	
	I2C_SDA_0();
	delay_us(4);
	
	I2C_SCL_0();  //钳住I2C总线，准备发送或接收数据 
}
 
//产生IIC停止信号
void I2C_Stop()
{
	I2C_SDA_Direction_Output(); //sda线输出
	I2C_SCL_0();
	I2C_SDA_0();
	delay_us(4);
	I2C_SCL_1();
	I2C_SDA_1();  //发送I2C总线结束信号
	delay_us(4);
}
 
/* 返回0表示正确应答，1表示无器件响应 */
u8 I2C_WaitAck()
{
	u8 ucErrTime = 0;
	I2C_SDA_Direction_Input();  //SDA设置为输入 
	I2C_SDA_1();
	delay_us(2);
	I2C_SCL_1();
	delay_us(2);
//	I2C_SDA_Direction_Input();
//	I2C_SDA_InputConfig();
	
//	if( I2C_SDA_READ() ) {
//		ack = 1;
//	}
//	else {
//		ack = 0;
//	}
		while( I2C_SDA_READ() )
		{
			ucErrTime ++;
			if(ucErrTime > 250)
			{
				I2C_Stop();
				return 1;
			}
		}
 
	I2C_SCL_0();
	return 0;
}
 
//产生ACK应答
// void I2C_Ack()
//{
//	I2C_SDA_0();	/* CPU驱动SDA = 0 */
//	delay_us(DELAYTIME);
//	
//	I2C_SCL_1();	/* CPU产生1个时钟 */
//	delay_us(DELAYTIME);
//	
//	I2C_SCL_0();
//	delay_us(DELAYTIME);
//	I2C_SDA_1();	/* CPU释放SDA总线 */
//}
//产生ACK应答
 void I2C_Ack()
{
	I2C_SCL_0();
	I2C_SDA_Direction_Output();
	I2C_SDA_0();	/* CPU驱动SDA = 1 */
	delay_us(2);
	
	I2C_SCL_1();	/* CPU产生1个时钟 */
	delay_us(2);
	
	I2C_SCL_0();
	
//	delay_us(2);
//	I2C_SDA_1();	/* CPU释放SDA总线 */
}
 
//不产生ACK应答	
void I2C_NAck()
{
//	I2C_SDA_1();	/* CPU驱动SDA = 1 */
//	delay_us(DELAYTIME);
//	
//	I2C_SCL_1();	/* CPU产生1个时钟 */
//	delay_us(DELAYTIME);
//	
//	I2C_SCL_0();
//	delay_us(DELAYTIME);
		I2C_SCL_0();
	I2C_SDA_Direction_Output();
	I2C_SDA_1();	/* CPU驱动SDA = 1 */
	delay_us(2);
	
	I2C_SCL_1();	/* CPU产生1个时钟 */
	delay_us(2);
	
	I2C_SCL_0();
}
void I2C_SendByte(u8 txd)
{
	u8 i;
	I2C_SDA_Direction_Output();
	I2C_SCL_0();//拉低时钟开始数据传输
	/* 先发送字节的高位bit7 */
	for (i = 0; i < 8; i++)
	{		
		if ((txd & 0x80)>>7)
			I2C_SDA_1();
		else
			I2C_SDA_0();
			txd<<=1;
		
		delay_us(2);
		I2C_SCL_1();
		delay_us(2);
		I2C_SCL_0();
		delay_us(2);
		
//		if (i == 7)
//		{
//			 I2C_SDA_1(); // 释放总线
//		}
//		_ucByte <<= 1;	/* 左移一个bit */
//		delay_us(DELAYTIME);
	}
}
 
u8 I2C_ReadByte(unsigned char ack)
{
	u8 i,receive=0;
	I2C_SDA_Direction_Input();
	
	for(i = 0;i < 8;i++)
	{
//		data <<= 1;
		I2C_SCL_0();
		delay_us(2);
		I2C_SCL_1();
//		I2C_SDA_Direction_Input();
		receive <<= 1;
		
		if( I2C_SDA_READ() ) 
			receive++;
			delay_us(1);
		}
		//I2C_SCL_0();
			
	    if (!ack)
        I2C_NAck();//发送nACK
    else
        I2C_Ack(); //发送ACK  
	return receive;
}
 
 

