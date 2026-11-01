#ifndef _K210_H_
#define _K210_H_
#include "ht32.h"
#include "ht32f5xxxx_ckcu.h"
#include "ht32f5xxxx_gpio.h"
#include "uart.h"
#include "string.h"
#include "stdio.h"
#include "oled.h"
#include "led.h"
void K210_proc(void);
void COM3_IRQHandler(void);
#endif



