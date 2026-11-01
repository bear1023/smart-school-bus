#include "My_servo.h"
#include "delay.h"
#include "time1.h"


void Servo_init(void)
{

	Servo_Run3(0);
	delay_ms(500);
	Servo_Run3(90);
	delay_ms(500);
//	Servo_Run(180);
//	Delay_ms(500);
}


/**
 * 功能：舵机驱动（可以从0-180）
 * 参数：angle 舵机旋转相对度数
 * 返回值：None
 */
void Servo_Run(uint16_t angle)
{
    switch(angle)
    {
		case 180 :TM_SetCaptureCompare(HT_GPTM0,TM_CH_0,175); break;//??180?
		case 135 :TM_SetCaptureCompare(HT_GPTM0,TM_CH_0,180); break;//??135?
		case 90  :TM_SetCaptureCompare(HT_GPTM0,TM_CH_0,185); break;//??90?
		case 45  :TM_SetCaptureCompare(HT_GPTM0,TM_CH_0,190); break;//??45?
		case 0   :TM_SetCaptureCompare(HT_GPTM0,TM_CH_0,195); break;//??0?
    }
}


void Servo_Run2(uint16_t angle)
{
    switch(angle)
    {
		case 180 :TM_SetCaptureCompare(HT_GPTM0,TM_CH_1,175); break;//??180?
		case 135 :TM_SetCaptureCompare(HT_GPTM0,TM_CH_1,180); break;//??135?
		case 90  :TM_SetCaptureCompare(HT_GPTM0,TM_CH_1,185); break;//??90?
		case 45  :TM_SetCaptureCompare(HT_GPTM0,TM_CH_1,190); break;//??45?
		case 0   :TM_SetCaptureCompare(HT_GPTM0,TM_CH_1,195); break;//??0?
    }
}


void Servo_Run3(uint16_t angle)
{
    switch(angle)
    {
		case 180 :TM_SetCaptureCompare(HT_GPTM0,TM_CH_2,175); break;//??180?
		case 135 :TM_SetCaptureCompare(HT_GPTM0,TM_CH_2,180); break;//??135?
		case 90  :TM_SetCaptureCompare(HT_GPTM0,TM_CH_2,185); break;//??90?
		case 45  :TM_SetCaptureCompare(HT_GPTM0,TM_CH_2,190); break;//??45?
		case 0   :TM_SetCaptureCompare(HT_GPTM0,TM_CH_2,195); break;//??0?
    }
}

void Servo_Run4(uint16_t angle)
{
    switch(angle)
    {
		case 180 :TM_SetCaptureCompare(HT_GPTM0,TM_CH_3,175); break;//??180?
		case 135 :TM_SetCaptureCompare(HT_GPTM0,TM_CH_3,180); break;//??135?
		case 90  :TM_SetCaptureCompare(HT_GPTM0,TM_CH_3,185); break;//??90?
		case 45  :TM_SetCaptureCompare(HT_GPTM0,TM_CH_3,190); break;//??45?
		case 0   :TM_SetCaptureCompare(HT_GPTM0,TM_CH_3,195); break;//??0?
    }
}

/* 重复定义已删除（原文件里 Servo_Run2/3/4 各出现两次，导致 Keil 编译报错） */


/* 重复定义已删除（原文件里 Servo_Run2/3/4 各出现两次，导致 Keil 编译报错） */

/* 重复定义已删除（原文件里 Servo_Run2/3/4 各出现两次，导致 Keil 编译报错） */
