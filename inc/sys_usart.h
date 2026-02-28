//
// Created by Simon Gong on 2026-02-21.
//

#ifndef AT32_BALANCE_V0_1_SYS_USART_H
#define AT32_BALANCE_V0_1_SYS_USART_H

#include <stdint.h>
#include <string.h>

#include "at32f403a_407.h"

#define BUFFER_SIZE 128
extern volatile uint8_t Tx3_buffer[BUFFER_SIZE];
extern volatile uint8_t Rx3_buffer[BUFFER_SIZE];
extern u8 sys_usart3_data[BUFFER_SIZE];
extern u8 sys_usart3_idle_flag;
extern volatile uint16_t sys_usart3_rx_len;

void sys_usart3_init(void);
uint32_t sys_usart3_send(const uint8_t *data, uint16_t len);

#endif //AT32_BALANCE_V0_1_SYS_USART_H