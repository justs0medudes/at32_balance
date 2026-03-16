//
// Created by xiaosai on 3/15/2026.
//

#ifndef AT32_BALANCE_V0_1_PERIPH_MOTOR_H
#define AT32_BALANCE_V0_1_PERIPH_MOTOR_H

#include <stdint.h>
void periph_motor1_set_pwm(uint16_t u, uint16_t v, uint16_t w);
void periph_motor2_set_pwm(uint16_t u, uint16_t v, uint16_t w);
void periph_motor1_test(void);
void periph_motor2_test(void);

#endif //AT32_BALANCE_V0_1_PERIPH_MOTOR_H