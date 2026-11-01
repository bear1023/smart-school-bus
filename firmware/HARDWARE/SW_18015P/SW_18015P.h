/*=================SW_18015P.h================*/
#ifndef _SW_18015P_H_
#define _SW_18015P_H_

#include "ht32f5xxxx_ckcu.h"
#include "ht32f5xxxx_gpio.h"
#include "ht32f5xxxx_01.h"

//端口号定义
#define HT_GPIO_PORT_SW_18015P HT_GPIOA

//引脚定义
#define SW_18015P_GPIO_PIN  GPIO_PIN_7
#define Read_STATE2() GPIO_ReadInBit(HT_GPIO_PORT_SW_18015P,SW_18015P_GPIO_PIN)   
void SW_18015P_Init(void);
int SW_18015P_test(void);

#endif