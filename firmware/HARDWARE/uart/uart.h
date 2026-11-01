#ifndef _UART_H
#define _UART_H
 
#include "ht32f5xxxx_01.h"
#include <stdio.h>
#include "time.h"
#define UART0_MAX_RECV_LEN		400					//最大接收缓存字节数
#define UART0_MAX_SEND_LEN		400					//最大发送缓存字节数
#define UART0_RX_EN 			1					//0,不接收;1,接收.

extern u8  UART0_RX_BUF[UART0_MAX_RECV_LEN]; 		//接收缓冲,最大USART2_MAX_RECV_LEN字节
extern u8  UART0_TX_BUF[UART0_MAX_SEND_LEN]; 		//发送缓冲,最大USART2_MAX_SEND_LEN字节
extern vu16 UART0_RX_STA;   						//接收数据状态


#define COM_PORT                   (HT_UART0)
#define COM_IRQn                   (UART0_IRQn)
#define COM_IRQHandler             (UART0_IRQHandler)
 
#define COM_TX_GPIO_ID             (GPIO_PC)
#define COM_TX_AFIO_PIN            (AFIO_PIN_4)
#define COM_TX_AFIO_MODE           (AFIO_FUN_USART_UART)
 
#define COM_RX_GPIO_ID             (GPIO_PC)
#define COM_RX_AFIO_PIN            (AFIO_PIN_5)
#define COM_RX_AFIO_MODE           (AFIO_FUN_USART_UART)
 

#define COM3_PORT                   (HT_UART1)
#define COM3_IRQn                   (UART1_IRQn)
#define COM3_IRQHandler             (UART1_IRQHandler)
 
#define COM3_TX_GPIO_ID             (GPIO_PC)
#define COM3_TX_AFIO_PIN            (AFIO_PIN_12)
#define COM3_TX_AFIO_MODE           (AFIO_FUN_USART_UART)
 
#define COM3_RX_GPIO_ID             (GPIO_PC)
#define COM3_RX_AFIO_PIN            (AFIO_PIN_13)
#define COM3_RX_AFIO_MODE           (AFIO_FUN_USART_UART) 

 
void UART0_Init(void);
void UART1_Init(void);
void Uart_Sendbyte(HT_USART_TypeDef* USARTx, u8 Data);
void Uart_SendArray(HT_USART_TypeDef* USARTx, u8 *array,u8 num);
void Uart_SendStr(HT_USART_TypeDef* USARTx, uint8_t *str);
 
#endif
