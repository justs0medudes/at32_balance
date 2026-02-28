/*
 * @file    sys_usart.c
 * @brief   usart setup and tx functions
 * @author  justsomedudes
 * @date    21 Feb 2026
 *
 * How to use:
 * 1. sys_usart3_send(), input message and the length
 * 2. check sys_usart3_idle_flag, if its set to 1 by the interrupt, then clear it and do whatever with sys_usart3_data
 */

#include "sys_usart.h"

#include "at32f403a_407_dma.h"
#include "at32f403a_407_usart.h"

#define BUFFER_SIZE 128

volatile uint8_t Tx3_buffer[BUFFER_SIZE];
volatile uint8_t Rx3_buffer[BUFFER_SIZE];
u8 sys_usart3_data[BUFFER_SIZE];
u8 sys_usart3_idle_flag = 0;
volatile uint16_t sys_usart3_rx_len = 0;

// currently set up for USART3 Tx
void sys_usart3_init(void) {
    usart_init(USART3, 115200, USART_DATA_8BITS, USART_STOP_1_BIT);
    usart_transmitter_enable(USART3, TRUE);
    usart_receiver_enable(USART3, TRUE);
    usart_parity_selection_config(USART3, USART_PARITY_NONE);

    usart_dma_receiver_enable(USART3, TRUE);
    usart_dma_transmitter_enable(USART3, TRUE);
    usart_hardware_flow_control_set(USART3, USART_HARDWARE_FLOW_NONE);
    usart_interrupt_enable(USART3, USART_IDLE_INT, TRUE);
    usart_enable(USART3, TRUE);
}

// polling function
/*
void sys_usart3_send(const uint8_t *data, uint16_t len) {
    if (len <= 128) {
        for (uint16_t i = 0; i < len; i++) {
            while (usart_flag_get(USART3, USART_TDBE_FLAG) == RESET) {}
            USART3->dt = data[i];
        }
    } else {
        const char *err = "Data is too long!\r\n";
        for (uint16_t i = 0; err[i] != '\0'; i++) {
            while (usart_flag_get(USART3, USART_TDBE_FLAG) == RESET) {}
            USART3->dt = err[i];
        }
    }
    while (usart_flag_get(USART3, USART_TDC_FLAG) == RESET);
}
*/

// send tx over dma controller
uint32_t sys_usart3_send(const uint8_t *data, uint16_t len) {
    if (len < BUFFER_SIZE) {
        memcpy((void*)Tx3_buffer, data, len);
        dma_channel_enable(DMA1_CHANNEL2, FALSE);
        dma_flag_clear(DMA1_FDT2_FLAG);
        DMA1_CHANNEL2->maddr = (uint32_t)Tx3_buffer;
        DMA1_CHANNEL2->dtcnt = len;
        dma_channel_enable(DMA1_CHANNEL2, TRUE);
    }
    return len;
}
