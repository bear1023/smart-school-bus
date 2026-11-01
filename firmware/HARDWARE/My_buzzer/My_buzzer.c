#include "My_buzzer.h"
#include "delay.h"

void Buzzer_init(void)
{
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  CKCUClock.Bit.PC    = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);



  GPIO_ClearOutBits       (HT_GPIOC ,GPIO_PIN_1);
  GPIO_DirectionConfig    (HT_GPIOC ,GPIO_PIN_1,GPIO_DIR_OUT);
  GPIO_PullResistorConfig(HT_GPIOC,GPIO_PIN_1,GPIO_PR_DISABLE);
  GPIO_DriveConfig(HT_GPIOC,GPIO_PIN_1,GPIO_DV_8MA);
}

void Buzzer_test(void)
{
	if(HT_CKCU->APBCCR1 & (1 << 4))
		WDT_Restart();
	GPIO_ClearOutBits(HT_GPIOC,GPIO_PIN_1);
	delay_ms(100);
	GPIO_SetOutBits(HT_GPIOC ,GPIO_PIN_1);
	delay_ms(100);
	GPIO_ClearOutBits(HT_GPIOC,GPIO_PIN_1);
	delay_ms(100);
	GPIO_SetOutBits(HT_GPIOC ,GPIO_PIN_1);
	delay_ms(100);


}