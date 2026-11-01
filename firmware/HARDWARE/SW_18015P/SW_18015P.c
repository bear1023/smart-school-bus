/*================infrared.c=============*/
#include "SW_18015P.h"
#include "led.h"
#include "My_buzzer.h"
#include "ht32.h"
#include "uart.h"
#include "string.h"
char temp1[20];
void SW_18015P_Init(void)
{
	CKCU_PeripClockConfig_TypeDef CKCUClock_SW_18015P= {{0}};
	CKCUClock_SW_18015P.Bit.PA = 1;  //开启GPIOA时钟
	CKCU_PeripClockConfig(CKCUClock_SW_18015P, ENABLE);
	GPIO_DirectionConfig(HT_GPIO_PORT_SW_18015P,SW_18015P_GPIO_PIN,GPIO_DIR_IN);
	GPIO_InputConfig(HT_GPIO_PORT_SW_18015P, SW_18015P_GPIO_PIN, ENABLE);
  	GPIO_PullResistorConfig(HT_GPIO_PORT_SW_18015P, SW_18015P_GPIO_PIN, GPIO_PR_UP);
}


//震动感应功能测试
//感应到人体输出高电平，离开感应区域输出低电平
int  SW_18015P_test(void)
{
	if( Read_STATE2() == RESET)
	{
		sprintf(temp1,"2");
		Uart_SendStr(COM_PORT,(uint8_t*)temp1);//发送数据给asppro模块 
		led_run2 (); //LED灯闪烁
		return 1;
		
	}
	else
	{
						  
		LED2_OFF();
		GPIO_ClearOutBits(HT_GPIOC ,GPIO_PIN_1);
				return 0;
	}
}
