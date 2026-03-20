/*
 * @file main.c
 * @brief main program
 * @author justsomedudes
 * @date 18 Feb 2026
 *
 */

#include <app_3pwm.h>
#include <app_encoder.h>
#include <cstdint>
#include <SimpleFOC.h>

extern "C" {
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
}

BLDCMotor motor1 = BLDCMotor(7);
BLDCMotor motor2 = BLDCMotor(7);

AT32Driver3PWM driver1 = AT32Driver3PWM(1);
AT32Driver3PWM driver2 = AT32Driver3PWM(2);

MA732Encoder encoder1 = MA732Encoder(1);
MA732Encoder encoder2 = MA732Encoder(2);

float target = 0; //default testing value
int main() {
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

    motor1.linkSensor(&encoder1);
    motor2.linkSensor(&encoder2);

    driver1.voltage_power_supply = 12.0f;
    driver2.voltage_power_supply = 12.0f;
    driver1.voltage_limit = 6.0f;
    driver2.voltage_limit = 6.0f;
    driver1.pwm_frequency = 20000;
    driver2.pwm_frequency = 20000;

    driver1.init();
    driver2.init();

    motor1.linkDriver(&driver1);
    motor2.linkDriver(&driver2);

    motor1.sensor_direction = CCW;
    motor2.sensor_direction = CCW;

    motor1.controller = MotionControlType::velocity;
    motor2.controller = MotionControlType::velocity;

    motor1.PID_velocity.P =0.2f;
    motor1.PID_velocity.I =2.0f;
    motor1.PID_velocity.D =0.0f;
    motor1.voltage_limit = 6.0f;
    motor1.PID_velocity.output_ramp = 150;
    motor1.LPF_velocity.Tf = 0.04f;

    motor2.PID_velocity.P =0.2f;
    motor2.PID_velocity.I =2.0f;
    motor2.PID_velocity.D =0.0f;
    motor2.voltage_limit = 6.0f;
    motor2.PID_velocity.output_ramp = 150;
    motor2.LPF_velocity.Tf = 0.04f;

    motor1.init();
    motor2.init();
    motor1.initFOC();
    motor2.initFOC();

    motor1.enable();
    motor2.enable();

    char buffer[64];
    uint32_t print_divider = 0;
    while (true) {
        motor1.loopFOC();
        motor2.loopFOC();
        motor1.move(target);
        motor2.move(-target);

        // Runs when signal is received
        if (sys_usart3_idle_flag == 1) {
            sys_usart3_idle_flag = 0;
            sys_usart3_data[sys_usart3_rx_len] = '\0';
            target = atof((char*)sys_usart3_data);
        }

        // Prints current velocity output for debug
        if (print_divider++ > 1000) {
            print_divider = 0;
            float vel = motor1.shaftVelocity();
            int32_t v = (int32_t)(vel * 100);
            sprintf(buffer, "V:%ld.%02ld\r\n", v/100, abs(v%100));
            sys_usart3_send((uint8_t*)buffer, strlen(buffer));
        }
    }
}
