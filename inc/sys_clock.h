#ifndef AT32_BALANCE_V0_1_SYS_CLOCK_H
#define AT32_BALANCE_V0_1_SYS_CLOCK_H

#include <stdint.h>

extern volatile uint32_t dbg_clk;
extern volatile uint32_t dbg_sclk;

void sys_clock_init(void);
void sys_periph_clock_init(void);
void sys_nvic_init(void);

#endif