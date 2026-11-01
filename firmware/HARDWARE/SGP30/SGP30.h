#ifndef __SGP30_H__
#define __SGP30_H__

#include "HT32.h"
#include "ht32_board.h"
#include "ht32_board_config.h"
#include "iic.h"

#define SGP30_read  0xb1           
#define SGP30_write 0xb0        
void SGP30_Init(void);				  
void SGP30_ad_write(u8 a, u8 b);
u32 SGP30_ad_read(void);



#endif
