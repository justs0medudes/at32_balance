/*
* @file   sys_tick.c
* @brief  Systick/timebase configuration
* @author justsomedudes
* @date   30 Jan 2026
*
* Responsibilities:
* - Configure SysTick for 1ms timebase
*
* Notes:
* 1) AHB block runs at 240 MHz, 1us = 240 cycles, 1ms = 240000 cycles
*/

#include "sys_tick.h"

#include "at32f403a_407.h"
#include "at32f403a_407_misc.h"

static volatile uint32_t g_ms = 0;

// Initialize SysTick for 1ms timebase
void sys_tick_init(const uint32_t core_hz)
{
    systick_clock_source_config(SYSTICK_CLOCK_SOURCE_AHBCLK_NODIV);

    SysTick->CTRL = 0;
    // 240000 cycles = 1ms (0 - 239999)
    SysTick->LOAD = core_hz / 1000U - 1U;
    // Clear current value
    SysTick->VAL = 0x00000000U;
    SysTick->CTRL = 
        SysTick_CTRL_CLKSOURCE_Msk |
        SysTick_CTRL_TICKINT_Msk |
        SysTick_CTRL_ENABLE_Msk;
}

// For use with delay functions
uint32_t sys_tick_ms(void)
{
    return g_ms;
}

// Adding to the counter on every SysTick interrupt
void sys_tick_isr(void)
{
    g_ms++;
}

