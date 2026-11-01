/*================infrared.c=============*/
#include "infrared.h"
/*================infrared.c=============*/
#include "infrared.h"

char temp[20];
void Infrared_Init(void)
{
	CKCU_PeripClockConfig_TypeDef CKCUClock_infrared= {{0}};
	CKCUClock_infrared.Bit.PB = 1;  //开启GPIOB时钟
	CKCU_PeripClockConfig(CKCUClock_infrared, ENABLE);
	GPIO_DirectionConfig(HT_GPIO_PORT_infrared,infrared_GPIO_PIN,GPIO_DIR_IN);
	GPIO_InputConfig(HT_GPIO_PORT_infrared, infrared_GPIO_PIN, ENABLE);
  	GPIO_PullResistorConfig(HT_GPIO_PORT_infrared, infrared_GPIO_PIN, GPIO_PR_DOWN);
}


//红外人体感应功能测试
//感应到人体输出高电平，离开感应区域输出低电平
void  infrared_test(void)
{
	if( Read_STATE() == RESET)
	{
		//OLED_ShowString(5,1, "that_no",13);
		LED1_OFF();	
	}
	else
	{
    //OLED_ShowString(5,2, "that_ok",13);
		delay_ms(5000);
		led_run();
		Buzzer_test();
		sprintf(temp,"1");
		Uart_SendStr(COM_PORT,(uint8_t*)temp);//发送数据给asppro模块 
	
	}
}

