# 固件说明

## 目录与职责

| 路径 | 职责 |
| --- | --- |
| `User/main.c` | 初始化 16 个外设 → ESP8266 联网 → 开机画面 → `while(1)` 轮询 |
| `User/ht32f5xxxx_01_it.c` | 中断向量模板（除启动文件默认处理外基本为空） |
| `HARDWARE/infrared/` | 人体红外：`Infrared_Init()`、`infrared_test()`（人离开 5 s 判定） |
| `HARDWARE/SW_18015P/` | 振动开关：`SW_18015P_Init()`、`SW_18015P_test()` |
| `HARDWARE/oled/` | SSD1306 软 I2C 驱动 + 字库 + 显存 |
| `HARDWARE/SGP30/` + `iic.c` | SGP30 TVOC/eCO₂ + 软件 I2C 底层 |
| `HARDWARE/mpu6050/` | MPU6050 六轴（`WHO_AM_I` 校验 + ACK 重试） |
| `HARDWARE/dht11/` | DHT11 单总线（未启用） |
| `HARDWARE/time1/`、`My_servo/` | GPTM0 50 Hz PWM + 舵机角度映射 |
| `HARDWARE/UART/`、`USART/` | 4 路串口、`printf` 重定向、`UsartPrintf` 变参 |
| `HARDWARE/onenet/onenet.c` | OneNET MQTT 组包（**全文注释，未实现**） |
| `NET/ESP8266/` | AT 指令状态机、缓冲管理 |
| `Utilities/ht32_board.c/h` | 板级初始化（时钟、GPIO 复用） |
| `Project/Templete.uvprojx` | Keil 工程（Target `Target 1`） |

## 主流程

```
main()
├─ OLED_Init / USART1(日志) / USART0(ESP) / UART0(语音) / UART1(K210)
├─ Led / PWM(GPTM0 CH2) / Buzzer / Key / Infrared / SW_18015P / SGP30
├─ ESP8266_Init()        // 阻塞 7 步 AT，无超时
├─ 开机画面（6 个汉字）→ 清屏
└─ while(1)
   ├─ OneNet_SendData()  // TODO: 未实现，已注释
   ├─ delay_ms(1000) → ESP8266_Clear()
   ├─ OLED_ShowPicture(BMP1)
   ├─ infrared_test()    // 含 delay_ms(5000)
   └─ SW_18015P_test()
```

## 中断清单

| 中断 | 处理函数 | 作用 |
| --- | --- | --- |
| `EXTI2_3_IRQHandler` | `My_key.c` | PB2 按键，翻转 `key_stat` |
| `UART0_IRQHandler` | `uart.c` | 语音模块收字节，`UART0_RX_STA` 高位作帧尾 |
| `USART0_IRQHandler` | `esp8266.c` | ESP8266 逐字节进 `esp8266_buf[256]` |
| `BFTM0_IRQHandler` | `uart.c` | 10 ms 帧超时，给 `UART0_RX_STA` 置帧尾 |
| `SysTick_Handler` | `ht32f5xxxx_01_it.c` | 空函数（时基用轮询 COUNTFLAG 实现） |

## 编译

1. Keil 装 `Holtek.HT32_DFP.1.0.44`；
2. 补回 `Libraries/`（盛群 HT32 SDK，仓库未随附）：`CMSIS`、`Device`、`HT32F5xxxx_Driver`、`HT32_USBD_Library`、`ht32_board_config.h`、`startup_ht32f5xxxx_cs3_01.s`；
3. 打开 `Project/Templete.uvprojx`，Target `Target 1`，芯片 HT32F52352；
4. 下载器选 Holtek CMSIS-DAP，Flash 算法 `HT32F.FLM`。

## 整理时的三处修复

原始工程构建日志是 `16 Error(s) / Target not created`，导致编译不过的三个原因已修：

| 文件 | 原问题 | 修复 |
| --- | --- | --- |
| `HARDWARE/My_servo/My_servo.c` | `Servo_Run2/3/4` 各定义两遍 | 删除重复块，保留首次定义 |
| `HARDWARE/infrared/infrared.h` | 第 1 行注释缺 `/*`，引起连锁语法错误 | 补上 `/*` |
| `User/main.c` | 调用未定义的 `OneNet_SendData()` | 注释掉并标 `TODO`，指向 `docs` 的状态说明 |

其余功能代码未改动。
