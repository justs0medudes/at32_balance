//
// Created by Simon Gong on 2026-02-25.
//

#ifndef AT32_BALANCE_V0_1_SYS_SPI_H
#define AT32_BALANCE_V0_1_SYS_SPI_H

#include "at32f403a_407_gpio.h"

// Encoder1
#define SPI1_0CS1 gpio_bits_set(GPIOD, GPIO_PINS_5)
#define SPI1_0CS0 gpio_bits_reset(GPIOD, GPIO_PINS_5)
// Encoder2
#define SPI1_1CS1 gpio_bits_set(GPIOD, GPIO_PINS_7)
#define SPI1_1CS0 gpio_bits_reset(GPIOD, GPIO_PINS_7)

// MPU line
#define SPI3_CS1 gpio_bits_set(GPIOA, GPIO_PINS_15)
#define SPI3_CS0 gpio_bits_reset(GPIOA, GPIO_PINS_15)

void sys_spi1_init(void);
void sys_spi3_init(void);
uint8_t sys_spi1_txrx(uint8_t data);
uint8_t sys_spi3_txrx(uint8_t data);

#endif //AT32_BALANCE_V0_1_SYS_SPI_H