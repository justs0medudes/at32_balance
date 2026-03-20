#ifndef AT32_BALANCE_V0_1_SYS_DELAY_H
#define AT32_BALANCE_V0_1_SYS_DELAY_H

#include <stdint.h>

#ifdef __cplusplus
    extern "C" {
#endif

void sys_delay_init(uint32_t core_hz);
void delay_ms(uint32_t ms);
void delay_us(uint32_t us);
uint32_t micros(void);

#ifdef __cplusplus
}
#endif

#endif
