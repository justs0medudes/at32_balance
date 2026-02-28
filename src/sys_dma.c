/*
 * @file    sys_dma.c
 * @brief   handles dma init functions
 * @author  justsomedudes
 * @data    21 Feb 2026
 */
#include "sys_dma.h"
#include "sys_usart.h"
#include "at32f403a_407_dma.h"

// DMA1 channel2, used for usart3 tx
void sys_dma1_channel2_init(void) {
    dma_init_type dma_init_struct;

    dma_reset(DMA1_CHANNEL2);
    dma_default_para_init(&dma_init_struct);
    dma_init_struct.direction = DMA_DIR_MEMORY_TO_PERIPHERAL;
    dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
    dma_init_struct.memory_inc_enable = TRUE;
    dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
    dma_init_struct.peripheral_inc_enable = FALSE;
    dma_init_struct.priority = DMA_PRIORITY_LOW;
    dma_init_struct.loop_mode_enable = FALSE;

    dma_init_struct.peripheral_base_addr = (uint32_t)&USART3->dt;
    dma_init_struct.memory_base_addr = (uint32_t)Tx3_buffer;
    dma_init_struct.buffer_size = 0;
    dma_init(DMA1_CHANNEL2, &dma_init_struct);

    dma_flexible_config(DMA1, FLEX_CHANNEL2, DMA_FLEXIBLE_UART3_TX);

    // dma_interrupt_enable(DMA1_CHANNEL2, DMA_FDT_INT, TRUE);
    dma_channel_enable(DMA1_CHANNEL2, FALSE);
}

// DMA1 channel1, used for usart3 rx (yet to be set up)
void sys_dma1_channel3_init(void) {
    dma_init_type dma_init_struct;

    dma_reset(DMA1_CHANNEL3);
    dma_default_para_init(&dma_init_struct);
    dma_init_struct.direction = DMA_DIR_PERIPHERAL_TO_MEMORY;
    dma_init_struct.memory_data_width = DMA_MEMORY_DATA_WIDTH_BYTE;
    dma_init_struct.memory_inc_enable = TRUE;
    dma_init_struct.peripheral_data_width = DMA_PERIPHERAL_DATA_WIDTH_BYTE;
    dma_init_struct.peripheral_inc_enable = FALSE;
    dma_init_struct.priority = DMA_PRIORITY_HIGH;
    dma_init_struct.loop_mode_enable = FALSE; // this is not using a ring buffer so no needd of loop mode

    dma_init_struct.peripheral_base_addr = (uint32_t)&USART3->dt;
    dma_init_struct.memory_base_addr = (uint32_t)Rx3_buffer;
    dma_init_struct.buffer_size = BUFFER_SIZE;
    dma_init(DMA1_CHANNEL3, &dma_init_struct);

    dma_flexible_config(DMA1, FLEX_CHANNEL3, DMA_FLEXIBLE_UART3_RX);

    // dma_interrupt_enable(DMA1_CHANNEL3, DMA_FDT_INT, TRUE);
    dma_channel_enable(DMA1_CHANNEL3, TRUE);
}

