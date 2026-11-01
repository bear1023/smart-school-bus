#include "ht32.h"



//输出四路PWM波控制后轮两个电机
//arr：自动重装值
//psc：时钟预分频数
//GT0 PA4 PA5 PA6 PA7
//产生一个20ms 定时周期 
void GPTM_PWM_init(void)
{
 
    TM_TimeBaseInitTypeDef TimeBaseIniture;   //结构体
    TM_OutputInitTypeDef   OutIniture;
 
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.PA         = 1;       //GPIOA时钟打开
    CKCUClock.Bit.AFIO       = 1;       //复用时钟
    CKCUClock.Bit.GPTM0      = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);      //时钟使能
//    AFIO_GPxConfig(GPIO_PA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, AFIO_MODE_4);  //开启复用功能
		AFIO_GPxConfig(GPIO_PA, GPIO_PIN_6, AFIO_MODE_4);  //开启复用功能
	GPIO_DirectionConfig(HT_GPIOA,GPIO_PIN_1,GPIO_DIR_OUT);
	TM_ClearFlag(HT_GPTM0, TM_FLAG_UEV);  //清除更新中断标志
    TM_OutputStructInit(&OutIniture);    //填写每个变量的默认值

    //定时器时基以及计数方式初始化

    TimeBaseIniture.CounterMode = TM_CNT_MODE_UP;            //边沿对齐向上模式
    TimeBaseIniture.CounterReload = 200-1;                       //计数重装载计数器
    TimeBaseIniture.Prescaler = 4800 -1;                           //预分频系数
    TimeBaseIniture.PSCReloadTime=TM_PSC_RLD_IMMEDIATE;    //立即重装载
    TM_TimeBaseInit(HT_GPTM0,&TimeBaseIniture);
 
////  0通道输出 PA4
//    OutIniture.Channel= TM_CH_0;
//    OutIniture.Control= TM_CHCTL_ENABLE;         //GPTM通道使能
//    OutIniture.OutputMode=TM_OM_PWM1 ;          //GPTM 通道 PWM1输出模式  PWM2模式翻转
//    OutIniture.Polarity= TM_CHP_INVERTED;    //GPTM 通道极性是低电平或下降沿      
//   // OutIniture.Compare=200;                      // 这个是配置占空比的
//    TM_OutputModeConfig(HT_GPTM0,TM_CH_0,TM_OM_PWM1);
//    TM_OutputInit(HT_GPTM0,&OutIniture);
 
// 
////  1通道输出 PA5
//    OutIniture.Channel=TM_CH_1;
//    OutIniture.Control=TM_CHCTL_ENABLE;         //GPTM通道使能
//    OutIniture.OutputMode=TM_OM_PWM1;          //GPTM 通道 PWM1输出模式  PWM2模式翻转
//    OutIniture.Polarity=TM_CHP_INVERTED;     //GPTM 通道极性是低电平或下降沿        
//    //OutIniture.Compare=200;                      // 这个是配置占空比的
//    TM_OutputModeConfig(HT_GPTM0,TM_CH_1,TM_OM_PWM1);
//    TM_OutputInit(HT_GPTM0,&OutIniture);


//  2通道输出 PA6
    OutIniture.Channel=TM_CH_2;
    OutIniture.Control=TM_CHCTL_ENABLE;         //GPTM通道使能
    OutIniture.OutputMode=TM_OM_PWM1;          //GPTM 通道 PWM1输出模式  PWM2模式翻转
    OutIniture.Polarity=TM_CHP_INVERTED;    //GPTM 通道极性是低电平或下降沿         
    //OutIniture.Compare=200;                      // 这个是配置占空比的
    TM_OutputModeConfig(HT_GPTM0,TM_CH_2,TM_OM_PWM1);
    TM_OutputInit(HT_GPTM0,&OutIniture);
 
////  3通道输出 PA7
//    OutIniture.Channel=TM_CH_3;
//    OutIniture.Control=TM_CHCTL_ENABLE;         //GPTM通道使能
//    OutIniture.OutputMode=TM_OM_PWM1;          //GPTM 通道 PWM1输出模式  PWM2模式翻转
//    OutIniture.Polarity=TM_CHP_INVERTED;    //GPTM 通道极性是低电平或下降沿        
//   // OutIniture.Compare=200;                      // 这个是配置占空比的
//    TM_OutputModeConfig(HT_GPTM0,TM_CH_3,TM_OM_PWM1);
//    TM_OutputInit(HT_GPTM0,&OutIniture);
	
    //TM_IntConfig(HT_GPTM0, TM_INT_CH0CC|TM_INT_CH1CC|TM_INT_CH2CC|TM_INT_CH3CC, ENABLE);  //中断		
		TM_IntConfig(HT_GPTM0, TM_INT_CH2CC, ENABLE);  //中断	
    TM_Cmd(HT_GPTM0,ENABLE);  //使能计数
}

