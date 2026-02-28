/*
 * @file main.c
 * @brief main program
 * @author justsomedudes
 * @date 18 Feb 2026
 *
 */

#include <stdint.h>

#include "sys_clock.h"
#include "sys_tmr.h"
#include "sys_gpio.h"
#include "periph_led.h"
#include "system_at32f403a_407.h"
#include "sys_delay.h"
#include "sys_dma.h"
#include "sys_tick.h"
#include "sys_usart.h"
#include "periph_mpu.h"

int main(void) {
    // Setup system clock, peripheral clocks, and NVIC
    sys_clock_init();
    sys_periph_clock_init();
    sys_nvic_init();
    sys_tick_init(system_core_clock);
    sys_delay_init(system_core_clock);

    sys_gpio_init();
    sys_tmr2_init();
    sys_usart3_init();
    sys_dma1_channel2_init();
    sys_dma1_channel3_init();

    periph_led_reset();
    periph_mpu_init();

    while (1) {
        // const char msg[] = "USART3 is working\r\n";
        /*
        if (sys_usart3_idle_flag == 1) {
            sys_usart3_idle_flag = 0;
            sys_usart3_send((uint8_t*)sys_usart3_data, sys_usart3_rx_len);
        }
        delay_ms(500);
        */
        periph_mpu_handle();
        delay_ms(50);
    }
}
