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
#include "periph_motor.h"
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
    sys_tmr1_init();
    sys_tmr2_init();
    sys_tmr8_init();
    sys_usart3_init();
    sys_dma1_channel2_init();
    sys_dma1_channel3_init();

    periph_led_reset();
    periph_mpu_init();
    periph_encoder_init();

    char buffer[64];
    while (1) {
        /* Usart Test*/
        // const char msg[] = "USART3 is working\r\n";
        /*
        if (sys_usart3_idle_flag == 1) {
            sys_usart3_idle_flag = 0;
            sys_usart3_send((uint8_t*)sys_usart3_data, sys_usart3_rx_len);
        }
        delay_ms(500);
        */

        /* loop speed test*/
        /*
        //static uint32_t counter;
        //counter++;
        if (print_divider >= 1000) {
            print_divider = 0;
            sprintf(buffer, "loops: %lu\r\n", counter);
            sys_usart3_send((uint8_t*)buffer, strlen(buffer));
            counter = 0;
        }
        */

        // periph_mpu_handle();
        periph_encoder_handle();

        static uint16_t print_divider;
        print_divider++;

        /* Encoder Test*/
        if (print_divider >= 50) {
            print_divider = 0;
            /* MPU Test*/
            // int32_t ax100 = (int32_t)(mpu.angle.x * 100.0f);
            // int32_t ay100 = (int32_t)(mpu.angle.y * 100.0f);
            int32_t e1 = (int32_t)(ma732.encoder1.diff_rad * 100.0f);
            int32_t e2 = (int32_t)(ma732.encoder2.diff_rad * 100.0f);
            sprintf(buffer,
                // "Angle X: %ld.%02ld Angle Y: %ld.%02ld\r\n",
                "E1: %ld.%02ld E2: %ld.%02ld\r\n",
                // ax100/100,labs(ax100%100),
                // ay100 / 100,labs(ay100 % 100));
                e1/100, labs(e1%100),
                e2/100, labs(e2%100));
            sys_usart3_send((uint8_t*)buffer, strlen(buffer));
        }
        // delay_ms(1);

        periph_motor1_test();
        periph_motor2_test();
        delay_ms(1);
    }
}
