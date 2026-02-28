//
// Created by Simon Gong on 2026-02-20.
//

#ifndef AT32_BALANCE_V0_1_PERIPH_LED_H
#define AT32_BALANCE_V0_1_PERIPH_LED_H

#include <stdint.h>

typedef enum {
    LED_OFF,
    LED_ON,
    LED_BLINK
} periph_led_actions_t;

typedef enum {
    R_LED = 0,
    G_LED = 1,
    B_LED = 2,
} periph_led_t;

void periph_led_actions(periph_led_t led, periph_led_actions_t action, uint32_t speed);
void periph_led_reset(void);

#endif //AT32_BALANCE_V0_1_PERIPH_LED_H