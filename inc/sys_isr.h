#ifndef AT32_BALANCE_V0_1_SYS_ISR_H
#define AT32_BALANCE_V0_1_SYS_ISR_H

#include <stdint.h>

// use extern here because the counter is used in other file
extern volatile uint32_t tmr2_counter;
void SysTick_Handler(void);
void TMR2_GLOBAL_IRQHandler(void);
void USART3_IRQHandler(void);

#endif