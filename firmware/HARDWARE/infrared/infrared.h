/**=================infrared.h================*/
#ifndef _INFRARED_H_
#define _INFRARED_H_

#include "ht32f5xxxx_ckcu.h"
#include "ht32f5xxxx_gpio.h"
#include "ht32f5xxxx_01.h"
#include "led.h"
#include "ht32.h"
#include "delay.h"
#include "infrared.h"
#include "uart.h"
#include "string.h"
#include "My_buzzer.h"
#include "oled.h"

//端口号定义
#define HT_GPIO_PORT_infrared HT_GPIOB

//引脚定义
#define infrared_GPIO_PIN  GPIO_PIN_1
#define Read_STATE() GPIO_ReadInBit(HT_GPIO_PORT_infrared,infrared_GPIO_PIN)   
void Infrared_Init(void);
void  infrared_test(void);

#endif