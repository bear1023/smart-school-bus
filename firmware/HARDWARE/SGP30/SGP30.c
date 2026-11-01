#include "SGP30.h"
#include "delay.h"

//**********************************操作函数****************************

//初始化IIC接口
void SGP30_Init(void)
{
	I2C_Initia();
	SGP30_ad_write(0x20,0x03);
//	SGP30_ad_write(0x20,0x61);
//	SGP30_ad_write(0x01,0x00);
}

void SGP30_ad_write(u8 a, u8 b)
{
  	I2C_Start();
  	I2C_SendByte(SGP30_write); //发送器件地址+写指令
		I2C_WaitAck();
  	I2C_SendByte(a);		//发送控制字节
		I2C_WaitAck();
		I2C_SendByte(b);
		I2C_WaitAck();
		I2C_Stop();
		delay_ms(100);
}

u32 SGP30_ad_read(void)
{
  	u32 dat;
		u8 crc;
  	I2C_Start();
  	I2C_SendByte(SGP30_read); //发送器件地址+读指令
		I2C_WaitAck();
  	dat = I2C_ReadByte(1);
		dat <<= 8;
		dat += I2C_ReadByte(1);
		crc = I2C_ReadByte(1); //crc数据，舍去
	  crc = crc;  //为了不让出现编译警告
		dat <<= 8;
		dat += I2C_ReadByte(1);
		dat <<= 8;
		dat += I2C_ReadByte(0);
  	I2C_Stop();
  	return(dat);
}
