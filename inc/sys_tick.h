#ifndef AT32_BALANCE_V0_1_SYS_TICK_H
#define AT32_BALANCE_V0_1_SYS_TICK_H

#include <stdint.h>

void sys_tick_init(uint32_t core_hz);
uint32_t sys_tick_ms(void);
void sys_tick_isr(void);

#endif

