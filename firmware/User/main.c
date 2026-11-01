#include "sys.h"
extern unsigned char BMP1[];

/* Private function prototypes -----------------------------------------------------------------------------*/
void MatrixKey_Lock_control(void);
void E_Init(void);
uint8_t data = 0;
uint8_t sendbuf[128] = {0};
extern	char buff[100];


/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main()
{
	
	OLED_Init();				          //OLED初始化
	OLED_Clear(0);						    //清屏
	USART1_Configuration();				//串口1，打印信息用
	USART0_Configuration();				//串口0，驱动ESP8266

	UART0_Init();                 //单线串口0，与asppro语音识别模块通信
  UART1_Init();                 //单线串口1，与K210通信	
	Led_Init(); 	                      //LED初始化
//	dou_dht11_init();                   //温湿度初始化
	GPTM_PWM_init();                    //PWM初始化
	Buzzer_init();                      //蜂鸣器初始化
	Key_Init();                         //按键初始化
	Infrared_Init();                    //人体模块初始化
	SW_18015P_Init();                   //震动模块初始化
	SGP30_Init();                       //气体传感器初始化

		ESP8266_Init();
	  delay_ms(500);
    OLED_ShowString(5,4, "esp_ok",13);
		OLED_Clear(0);							//清屏
		OLED_ShowCHinese_five(0,0,0);
		OLED_ShowCHinese_five(16,0,1);
		OLED_ShowCHinese_five(32,0,10);
		OLED_ShowCHinese_five(48,0,11);    
		OLED_ShowCHinese_five(64,0,4);
		OLED_ShowCHinese_five(80,0,5);  
    //OLED显示指纹连接成功	
			delay_ms (2000);
			OLED_Clear(0);
      delay_ms (2000);			//清屏
    

	while(1)
	{
//      
//		  dou_dht11_get_data();//获取温度数据
//		
			// OneNet_SendData();  // TODO: OneNET 属性上报尚未实现（工程里没有该函数定义），见 docs/03-status.md
		
   		delay_ms(1000);
		
		  ESP8266_Clear();	 //清除数据
		
      OLED_ShowPicture(0,0,128,64,BMP1,1); 		//显示表情包
	
	    infrared_test();                          //人员逗留
    
	    SW_18015P_test();		                  //安全就座，振动模块
}	

}

