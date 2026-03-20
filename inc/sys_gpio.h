#ifndef AT32_BALANCE_V0_1_SYS_GPIO_H
#define AT32_BALANCE_V0_1_SYS_GPIO_H

#include "at32f403a_407_gpio.h"

#define MOTOR_EN1 gpio_bits_set(GPIOE, GPIO_PINS_7);
#define MOTOR_EN0 gpio_bits_reset(GPIOE, GPIO_PINS_7);

void sys_gpio_init(void);

#endif