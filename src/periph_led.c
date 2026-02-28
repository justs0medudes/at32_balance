/*
 * @file    periph_led.c
 * @brief   a simple led function that runs on TMR2
 * @author  justsomedudes
 * @date    20 Feb 2026
 *
 * Notes:
 * This function runs on TMR2, which means the timing function is already integrated for the blink mode
 *
 * How to use:
 * Call periph_led_actions(), then input the led (R_LED, G_LED, or B_LED), the action (LED_ON, LED_OFF, or LED_BLINK)
 * and the blinking speed if you are using LED_BLINK
 */

#include "periph_led.h"

#include "sys_isr.h"

#include "at32f403a_407_gpio.h"


void periph_led_actions(periph_led_t led, periph_led_actions_t actions, uint32_t speed) {
    static uint32_t last_time[3] = {0, 0, 0};
    switch (actions) {
        case LED_ON:
            switch (led) {
                case 0: gpio_bits_write(GPIOC, GPIO_PINS_13, FALSE); break;
                case 1: gpio_bits_write(GPIOC, GPIO_PINS_14, FALSE); break;
                case 2: gpio_bits_write(GPIOC, GPIO_PINS_15, FALSE); break;
                default: break;
            }
            break;
        case LED_OFF:
            switch (led) {
                case 0: gpio_bits_write(GPIOC, GPIO_PINS_13, TRUE); break;
                case 1: gpio_bits_write(GPIOC, GPIO_PINS_14, TRUE); break;
                case 2: gpio_bits_write(GPIOC, GPIO_PINS_15, TRUE); break;
                default: break;
            }
            break;
        case LED_BLINK:
            if (tmr2_counter - last_time[led] >= speed) {
                switch (led) {
                    case 0: gpio_bits_toggle(GPIOC, GPIO_PINS_13); break;
                    case 1: gpio_bits_toggle(GPIOC, GPIO_PINS_14); break;
                    case 2: gpio_bits_toggle(GPIOC, GPIO_PINS_15); break;
                    default: break;
                }
                last_time[led] = tmr2_counter;
            }
            break;
    }
}

void periph_led_reset(void) {
    gpio_bits_set(GPIOC, GPIO_PINS_13 | GPIO_PINS_14 | GPIO_PINS_15);
}