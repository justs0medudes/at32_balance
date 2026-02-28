#ifndef AT32_BALANCE_V0_1_SYS_DELAY_H
#define AT32_BALANCE_V0_1_SYS_DELAY_H

#include <stdint.h>

void sys_delay_init(uint32_t core_hz);
void delay_ms(uint32_t ms);
void delay_us(uint32_t us);

#endif
