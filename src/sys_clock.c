/*
* @file   sys_clock.c
* @brief  System clock and core initialization
* @author justsomedudes
* @date   29 Jan 2026
*
* Responsibilities:
* - Configure system clock tree (HEXT + PLL)
* - Set AHB, APB prescalers
* - Enable required peripheral clocks (GPIOA-D, IOMUX)
* - Configure system interrupts (NVIC) priorities
*
* Notes:
* 1) Board uses 25 MHz HEXT crystal running on crystal resonator mode
* 2) Sysclk = 240 MHz (HEXT/5 * 48)
*/
#include "sys_clock.h"
#include "sys_delay.h"
#include "at32f403a_407.h"

// Include debug variables
volatile uint32_t dbg_clk;
volatile uint32_t dbg_sclk; 

// Configure the system clock
void sys_clock_init(void)
{
    crm_reset();
    // Enable LICK
    crm_clock_source_enable(CRM_CLOCK_SOURCE_LICK, TRUE);
    while (crm_flag_get(CRM_LICK_STABLE_FLAG) != SET) {}

    // Enable HEXT
    crm_clock_source_enable(CRM_CLOCK_SOURCE_HEXT, TRUE);
    while (crm_hext_stable_wait() == ERROR) {}
    crm_hext_clock_div_set(CRM_HEXT_DIV_5);

    // Configure PLL (5*48MHz=240MHz)
    crm_pll_config(CRM_PLL_SOURCE_HEXT_DIV, CRM_PLL_MULT_48, CRM_PLL_OUTPUT_RANGE_GT72MHZ);
    crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);
    while (crm_flag_get(CRM_PLL_STABLE_FLAG) != SET) {}

    // Set AHB/APB dividers
    crm_ahb_div_set(CRM_AHB_DIV_1);
    crm_apb1_div_set(CRM_APB1_DIV_2);
    crm_apb2_div_set(CRM_APB2_DIV_2);

    // Set sysclk to run on PLL clock, output debug variable and kill it if failed
    crm_auto_step_mode_enable(TRUE);
    crm_sysclk_switch(CRM_SCLK_PLL);
    while(crm_sysclk_switch_status_get() != CRM_SCLK_PLL) {}
    dbg_sclk = crm_sysclk_switch_status_get();
    crm_auto_step_mode_enable(FALSE);

    system_core_clock_update();
    dbg_clk = system_core_clock;
}

// Configure peripheral clocks
void sys_periph_clock_init(void)
{
    crm_periph_clock_enable(CRM_DMA1_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOC_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_SPI3_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_TMR2_PERIPH_CLOCK, TRUE);
    crm_periph_clock_enable(CRM_USART3_PERIPH_CLOCK, TRUE);
}

// Configure system interrupts (NVIC)
void sys_nvic_init(void)
{
    nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);

    NVIC_SetPriority(MemoryManagement_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_SetPriority(BusFault_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_SetPriority(UsageFault_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_SetPriority(SVCall_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_SetPriority(DebugMonitor_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_SetPriority(PendSV_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 15, 0));
    nvic_irq_enable(TMR2_GLOBAL_IRQn, 0, 0);
    nvic_irq_enable(USART3_IRQn, 0, 0);
    nvic_irq_enable(DMA1_Channel1_IRQn, 0, 0);
    nvic_irq_enable(DMA1_Channel2_IRQn, 0, 0);
}

