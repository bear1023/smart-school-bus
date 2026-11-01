#ifndef _IIC_H
#define _IIC_H
 
#include "ht32f5xxxx_01.h"
 
/* 定义I2C的SCL连接的GPIO端口 */
#define I2C_SCL_GPIO_ID					GPIO_PA					/* GPIO端口 */
#define I2C_SCL_PIN						GPIO_PIN_0				/* 连接到SCL时钟线的GPIO */
#define I2C_SCL_AFIO_MODE				AFIO_FUN_GPIO
#define I2C_SCL_PORT					HT_GPIOA
 
/* 定义I2C的SDA连接的GPIO端口 */
#define I2C_SDA_GPIO_ID					GPIO_PA					/* GPIO端口 */
#define I2C_SDA_PIN						GPIO_PIN_1				/* 连接到SCL时钟线的GPIO */
#define I2C_SDA_AFIO_MODE				AFIO_FUN_GPIO
#define I2C_SDA_PORT					HT_GPIOA
//IO操作函数 
#define I2C_SCL_1()						GPIO_SetOutBits(I2C_SCL_PORT, I2C_SCL_PIN)  // 高电平
#define I2C_SCL_0()						GPIO_ClearOutBits(I2C_SCL_PORT, I2C_SCL_PIN) //低电平	
#define I2C_SDA_1()						GPIO_SetOutBits(I2C_SDA_PORT, I2C_SDA_PIN)
#define I2C_SDA_0()						GPIO_ClearOutBits(I2C_SDA_PORT, I2C_SDA_PIN)
#define I2C_SDA_READ()					GPIO_ReadInBit(I2C_SDA_PORT, I2C_SDA_PIN) //输入SDA
 
//IO方向设置
#define I2C_SDA_Direction_Input()		GPIO_DirectionConfig(I2C_SDA_PORT, I2C_SDA_PIN, GPIO_DIR_IN)
#define I2C_SDA_Direction_Output()		GPIO_DirectionConfig(I2C_SDA_PORT, I2C_SDA_PIN, GPIO_DIR_OUT) //SDA线输出
 
#define I2C_SDA_InputConfig()			GPIO_InputConfig(I2C_SDA_PORT, I2C_SDA_PIN, ENABLE) //使能输入输出
#define I2C_SDA_InputDisable()			GPIO_InputConfig(I2C_SDA_PORT, I2C_SDA_PIN, DISABLE)
 
 
 
void I2C_Initia(void);
void I2C_Start(void);
void I2C_Stop(void);
u8 I2C_WaitAck(void);
void I2C_SendByte(u8 _ucByte);
u8 I2C_ReadByte(unsigned char ack);
void I2C_Ack(void);
void I2C_NAck(void);
 
 
#endif


