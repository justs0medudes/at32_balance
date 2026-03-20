/*
 * @file    sys_gpio.c
 * @brief   Initialize GPIO
 * @author  justsomedudes
 * @date    18 Feb 2026
 *
 */

#include "sys_gpio.h"

#include "at32f403a_407_gpio.h"

// configures all the GPIO pins
void sys_gpio_init(void) {

    gpio_init_type gpio_init_struct;
    gpio_default_para_init(&gpio_init_struct);

    // configure LED pins (PC13, PC14, PC15)
    gpio_bits_reset(GPIOC, GPIO_PINS_13 | GPIO_PINS_14 | GPIO_PINS_15);
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_pins = GPIO_PINS_13 | GPIO_PINS_14 | GPIO_PINS_15;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(GPIOC, &gpio_init_struct);

    // configure TX pin (PD8)
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_pins = GPIO_PINS_8;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(GPIOD, &gpio_init_struct);

    // configure RX pin (PD9)
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
    gpio_init_struct.gpio_pins = GPIO_PINS_9;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(GPIOD, &gpio_init_struct);

    gpio_pin_remap_config(USART3_GMUX_0011, TRUE);

    // configure SPI1 pins (MA732)
    gpio_pin_remap_config(SPI1_GMUX_0001, TRUE);
    gpio_init_struct.gpio_pins = GPIO_PINS_3 | GPIO_PINS_4 | GPIO_PINS_5;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_UP;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init(GPIOB, &gpio_init_struct);

    gpio_init_struct.gpio_pins = GPIO_PINS_5 | GPIO_PINS_7;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init(GPIOD, &gpio_init_struct);

    // configure SPI3 pins (MPU6500)
    gpio_pin_remap_config(SPI3_GMUX_0011, TRUE);
    gpio_pin_remap_config(SWJTAG_GMUX_010, TRUE); // not sure what this does yet
    gpio_init_struct.gpio_pins = GPIO_PINS_10 | GPIO_PINS_11 | GPIO_PINS_12;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_UP;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init(GPIOC, &gpio_init_struct);
    
    gpio_init_struct.gpio_pins = GPIO_PINS_15;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init(GPIOA, &gpio_init_struct);

    // Configure TMR1 pins
    gpio_pin_remap_config(TMR1_GMUX_0011, TRUE);
    gpio_init_struct.gpio_pins = GPIO_PINS_8 | GPIO_PINS_9 | GPIO_PINS_10 | GPIO_PINS_11 | GPIO_PINS_12 | GPIO_PINS_13;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init(GPIOE, &gpio_init_struct);

    gpio_init_struct.gpio_pins = GPIO_PINS_7;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init(GPIOE, &gpio_init_struct);

    // gpio_bits_set(GPIOE, GPIO_PINS_7);

    // Configure TMR8 pins
    gpio_init_struct.gpio_pins = GPIO_PINS_7;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init(GPIOA, &gpio_init_struct);

    /* timer8 output pin Configuration */
    gpio_init_struct.gpio_pins = GPIO_PINS_0 | GPIO_PINS_1;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init(GPIOB, &gpio_init_struct);

    /* timer8 output pin Configuration */
    gpio_init_struct.gpio_pins = GPIO_PINS_6 | GPIO_PINS_7 | GPIO_PINS_8;
    gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    gpio_init(GPIOC, &gpio_init_struct);
}
