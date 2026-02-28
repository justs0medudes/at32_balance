/*
* @file   sys_isr.c
* @brief  System interrupt service routines
* @author justsomedudes
* @date   30 Jan 2026
*
*/

#include "sys_isr.h"
#include "sys_tick.h"
#include "sys_usart.h"
#include "at32f403a_407.h"
#include "at32f403a_407_tmr.h"

volatile uint32_t tmr2_counter = 0;

void SysTick_Handler(void) {
    sys_tick_isr();
}

// If interrupt is triggered, then update tmr2_counter
// tmr2_counter is used for determine time
void TMR2_GLOBAL_IRQHandler(void) {
    if (tmr_flag_get(TMR2, TMR_OVF_FLAG) != RESET) {
        tmr_flag_clear(TMR2, TMR_OVF_FLAG);
        tmr2_counter++;
    }
}


void USART3_IRQHandler(void) {
    if (usart_flag_get(USART3, USART_IDLEF_FLAG) != RESET) {
        u16 len = 0;
        usart_flag_clear(USART3, USART_IDLEF_FLAG);
        len = BUFFER_SIZE - dma_data_number_get(DMA1_CHANNEL3);

        if (len < BUFFER_SIZE) memcpy(sys_usart3_data, (const uint8_t*)Rx3_buffer, len);
        dma_channel_enable(DMA1_CHANNEL3, FALSE);
        dma_data_number_set(DMA1_CHANNEL3, BUFFER_SIZE);
        dma_channel_enable(DMA1_CHANNEL3, TRUE);

        sys_usart3_rx_len = len;
        sys_usart3_idle_flag = 1;
    }
}
