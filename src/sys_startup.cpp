//
// Created by Simon Gong on 2026-05-15.
//

#include "sys_startup.h"
#include "at32f403a_407.h"

void sys_startup(void) {
    gpio_bits_set(GPIOD, GPIO_PINS_11); // latch the power immediately after startup


}