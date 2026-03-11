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
#include "periph_encoder.h"

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
    periph_encoder_init();

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
        periph_encoder_handle();
        char buffer[64];

        static uint16_t print_divider;
        print_divider++;

        if (print_divider >= 50) {
            print_divider = 0;
            int32_t ax100 = (int32_t)(mpu.angle.x * 100.0f);
            int32_t ay100 = (int32_t)(mpu.angle.y * 100.0f);
            int32_t e1 = (int32_t)(ma732.encoder1.diff * 100.0f);
            // int32_t e2 = (int32_t)(ma732.encoder2.diff * 100.0f);
            sprintf(buffer,
                // "Angle X: %ld.%02ld Angle Y: %ld.%02ld
                "E1: %ld.%02ld\r\n",
                // ax100/100,labs(ax100%100),
                // ay100 / 100,labs(ay100 % 100),
                e1/100, labs(e1%100));
            sys_usart3_send((uint8_t*)buffer, strlen(buffer));
        }
        delay_ms(1);
    }
}
