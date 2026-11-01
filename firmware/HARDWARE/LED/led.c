#include "led.h"
#include "delay.h"
#include "ht32.h"

void Led_Init(void)
{
		

  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  CKCUClock.Bit.PC    = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);


  GPIO_DirectionConfig    (HT_GPIOC ,GPIO_PIN_14,GPIO_DIR_OUT);
  
  GPIO_PullResistorConfig (HT_GPIOC,GPIO_PIN_14,GPIO_PR_DOWN);
  GPIO_DirectionConfig    (HT_GPIOC ,GPIO_PIN_15,GPIO_DIR_OUT);
  
  GPIO_PullResistorConfig (HT_GPIOC,GPIO_PIN_15,GPIO_PR_DOWN);



}
void LED1_OFF(void)
{
	GPIO_ClearOutBits(HT_GPIOC, GPIO_PIN_14);
}

void LED1_ON(void)
{
	GPIO_SetOutBits(HT_GPIOC, GPIO_PIN_14);
}


void LED2_OFF(void)
{
	GPIO_ClearOutBits(HT_GPIOC, GPIO_PIN_15);
}

void LED2_ON(void)
{
	GPIO_SetOutBits(HT_GPIOC, GPIO_PIN_15);
}
void led_run (void )
{
	LED1_ON();
	delay_ms(500);
	LED1_OFF();
	delay_ms(500);
}

