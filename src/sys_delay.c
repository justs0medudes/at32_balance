/*
* @file     sys_delay.c
* @brief    Delay functions
* @author   justsomedudes
* @date     31 Jan 2026
*
*/

#include "sys_delay.h"
#include "sys_tick.h"
#include "at32f403a_407.h"

static uint32_t g_core_hz = 0;

// initilizing CYCCNT counter
void sys_delay_init(const uint32_t core_hz)
{
    g_core_hz = core_hz;

    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

}

// ms counter using systick interrupt
void delay_ms(uint32_t ms)
{
    uint32_t start = sys_tick_ms(); // start = g_ms counter
    while (sys_tick_ms() - start < ms)
    {
        __NOP();
    }
}

// us counter using CYCCNT
void delay_us(uint32_t us)
{
    uint32_t start = DWT->CYCCNT;
    uint32_t cycles = (uint32_t)(((uint64_t)g_core_hz * us) / 1000000ULL);

    while (DWT->CYCCNT - start < cycles)
    {
        __NOP();
    }
}

uint32_t micros(void) {
    return DWT->CYCCNT / (g_core_hz / 1000000U);
}