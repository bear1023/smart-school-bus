#include "uart.h"
#include "time.h"

u8 UART0_RX_BUF[UART0_MAX_RECV_LEN]; 				//接收缓冲,最大UART0_MAX_RECV_LEN个字节.
u8 UART0_TX_BUF[UART0_MAX_SEND_LEN]; 			  //发送缓冲,最大UART0_MAX_SEND_LEN字节
vu16 UART0_RX_STA=0;  

/**************************实现函数********************************************
函数说明：配置uart0串口

*******************************************************************************/ 
static void UART0_CKCU_Config()
{
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
	
	CKCUClock.Bit.AFIO=1;
	CKCUClock.Bit.PC=1;			
	CKCUClock.Bit.UART0= 1;
	CKCU_PeripClockConfig(CKCUClock, ENABLE);
}

static void UART0_AFIO_Config()
{
	GPIO_PullResistorConfig(HT_GPIOC, GPIO_PIN_5, GPIO_PR_UP);
	AFIO_GPxConfig(COM_TX_GPIO_ID, COM_TX_AFIO_PIN, AFIO_FUN_USART_UART);
	AFIO_GPxConfig(COM_RX_GPIO_ID, COM_RX_AFIO_PIN, AFIO_FUN_USART_UART);
}

static void UART0_Config()
{
	USART_InitTypeDef USART_InitStructure;
	
	/*USART初始化
	*波特率：115200
	*字节长度：8位
	*停止位：1位
	*校验位：无			
	*模式：正常模式
	**/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
	USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
	USART_InitStructure.USART_Parity = USART_PARITY_NO;
	USART_InitStructure.USART_Mode = USART_MODE_NORMAL;
	USART_Init(COM_PORT  , &USART_InitStructure);
	
	/* 设置USART中断标志 */
	USART_IntConfig(COM_PORT, USART_INT_RXDR, ENABLE);
	/* 使能USART接收、发送 */
	USART_TxCmd(COM_PORT, ENABLE);
	USART_RxCmd(COM_PORT, ENABLE);
	/* 初始化中断 */
	NVIC_EnableIRQ(COM_IRQn);
	
	
	Timer0_Init();
  UART0_RX_STA=0;		//清零
}

void UART0_Init()
{
	UART0_CKCU_Config();
	UART0_AFIO_Config();
	UART0_Config();
}
 

/**************************实现函数********************************************
函数说明：配置uart1串口

*******************************************************************************/ 

/**************************实现函数********************************************
函数说明：配置uart0串口

*******************************************************************************/ 
static void UART1_CKCU_Config()
{
	CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
	
	CKCUClock.Bit.AFIO=1;
	CKCUClock.Bit.PC=1;			
	CKCUClock.Bit.UART1= 1;
	CKCU_PeripClockConfig(CKCUClock, ENABLE);
}

static void UART1_AFIO_Config()
{
	GPIO_PullResistorConfig(HT_GPIOC, GPIO_PIN_13, GPIO_PR_UP);
	AFIO_GPxConfig(COM3_TX_GPIO_ID, COM3_TX_AFIO_PIN, AFIO_FUN_USART_UART);
	AFIO_GPxConfig(COM3_RX_GPIO_ID, COM3_RX_AFIO_PIN, AFIO_FUN_USART_UART);
}

static void UART1_Config()
{
	USART_InitTypeDef USART_InitStructure;
	
	/*USART初始化
	*波特率：115200
	*字节长度：8位
	*停止位：1位
	*校验位：无			
	*模式：正常模式
	**/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
	USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
	USART_InitStructure.USART_Parity = USART_PARITY_NO;
	USART_InitStructure.USART_Mode = USART_MODE_NORMAL;
	USART_Init(COM3_PORT  , &USART_InitStructure);
	
	/* 设置USART中断标志 */
	USART_IntConfig(COM3_PORT, USART_INT_RXDR, ENABLE);
	/* 使能USART接收、发送 */
	USART_TxCmd(COM3_PORT, ENABLE);
	USART_RxCmd(COM3_PORT, ENABLE);
	/* 初始化中断 */
	NVIC_EnableIRQ(COM3_IRQn);
	
}

void UART1_Init()
{
	UART1_CKCU_Config();
	UART1_AFIO_Config();
	UART1_Config();
}








// 发送一个字节
void Uart_Sendbyte(HT_USART_TypeDef* USARTx, u8 Data)
{
	USART_SendData(COM_PORT, Data);
	// 等待发送数据寄存器清空
	while (USART_GetFlagStatus(COM_PORT, USART_FLAG_TXDE) == RESET);		
}
 
//发送每个元素数据长度为8位的数组
void Uart_SendArray(HT_USART_TypeDef* USARTx, u8 *array,u8 num)
{
	u8 i;
	for( i = 0;i < num;i++)
	{
		Uart_Sendbyte(USARTx,*array);
		array++;
	}
}
 
// 发送字符串
void Uart_SendStr(HT_USART_TypeDef* USARTx, uint8_t *str)
{
	uint8_t i;
	for(i = 0;str[i] != '\0';i++)
	{
		Uart_Sendbyte(USARTx,str[i]);
	}
}


void UART0_IRQHandler(void)
{
		u8 res;	      
	if( USART_GetFlagStatus(COM_PORT, USART_FLAG_RXDR ) )//接收到数据
	{	 
		
		res =USART_ReceiveData(COM_PORT);		
	 
		if(UART0_RX_STA<UART0_MAX_RECV_LEN)	//还可以接收数据
		{
//				TIM_SetCounter(TIM4,0);//计数器清空          				//计数器清空
				if(UART0_RX_STA==0) 				//使能定时器4的中断 
				{
//					TIM_Cmd(TIM4,ENABLE);//使能定时器4
			      BFTM_EnaCmd(HT_BFTM0, ENABLE);//使能BFTM
				}
			
			 UART0_RX_BUF[UART0_RX_STA++]=res;	//记录接收到的值
		
		}
		else 
			{
				UART0_RX_STA|=1<<15;				//强制标记接收完成
			} 
			USART_ClearFlag(COM_PORT, USART_FLAG_RSADD);
		}
}


//void COM3_IRQHandler(void)
//{
//	u8 data;
//	
//	if( USART_GetFlagStatus(COM3_PORT, USART_FLAG_RXDR ) )         //接收中断
//	{
//		data = USART_ReceiveData(COM3_PORT);                         //读取接收到的数据
//		printf("data = %c\n",data);                                  //把收到的数据发送回电脑		
//	}
//}


