#ifndef __MY_KEY_H__
#define __MY_KEY_H__

#include "ht32.h"
#include "ht32f5xxxx_ckcu.h"
#include "ht32f5xxxx_gpio.h"
#include "ht32f5xxxx_01.h"
#include "led.h"

//定义使用端口
#define HT_GPIO_GROUP     (HT_GPIOB)

//引脚定义
#define GPIO_PIN   				(GPIO_PIN_2 |GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5)
//定义方式
#define GPIO_PR           (GPIO_PR_UP)
//定义模式
#define GPIO_FIFO_MODE    (AFIO_FUN_GPIO)

void Key_Init(void);
void EXTI4_15_IRQHandler(void);
void EXTI2_3_IRQHandler(void);


#endif
