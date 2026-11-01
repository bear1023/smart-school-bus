#include "K210.h"

volatile uint8_t k210_rx_flag = 0;

// COM3 中断处理函数（UART1 接收中断）
void COM3_IRQHandler(void)
{
    if (USART_GetFlagStatus(COM3_PORT, USART_FLAG_RXDR))
    {
        uint8_t data = USART_ReceiveData(COM3_PORT);
        if (data == '1')
        {
            k210_rx_flag = 1;  // 设置标志位
        }
        USART_ClearFlag(COM3_PORT, USART_FLAG_RXDR); // 清除中断标志
    }
}

void K210_proc(void)
{
    static uint8_t last_state = 0; // 记录上一次状态，避免重复刷新 OLED

    if (k210_rx_flag)
    {
        k210_rx_flag = 0; // 清除标志位

        LED1_ON(); // 点亮 LED1

        // 发送 "2" 到串口0
        Uart_SendStr(COM_PORT, (uint8_t*)"3");

        // 更新 OLED 显示（仅在状态变化时刷新）
        if (last_state != 1)
        {
            OLED_ShowString(4, 5, "student_on_car", 15);
            last_state = 1;
        }
    }
    else
    {
        // 可选：若无持续接收需求，可关闭 LED
        LED1_OFF();
    }
}

