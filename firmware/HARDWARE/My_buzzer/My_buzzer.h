#ifndef __MY_BUZZER_H__
#define __MY_BUZZER_H__

#include "ht32.h"
#include "Delay.h"

//-----------------------------------------------------------------------------

#define OUT_PA0_PORT           A
#define OUT_PA0_PIN            0
#define OUT_PA0_GPIO_CLK      STRCAT2(P,          OUT_PA0_PORT)
#define OUT_PA0_GPIO_ID       STRCAT2(GPIO_P,     OUT_PA0_PORT)
#define OUT_PA0_GPIO_PORT     STRCAT2(HT_GPIO,    OUT_PA0_PORT)
#define OUT_PA0_GPIO_PIN      STRCAT2(GPIO_PIN_,  OUT_PA0_PIN)
#define OUT_PA0_AFIO_MODE     (AFIO_MODE_GPIO)
#define OUT_PA0_HIGH          OUT_PA0_GPIO_PORT->SRR    = OUT_PA0_GPIO_PIN
#define OUT_PA0_LOW           OUT_PA0_GPIO_PORT->RR     = OUT_PA0_GPIO_PIN
#define OUT_PA0_XOR           OUT_PA0_GPIO_PORT->DOUTR ^= OUT_PA0_GPIO_PIN

//-----------------------------------------------------------------------------
void Buzzer_init(void);
void Buzzer_test(void);

#endif

