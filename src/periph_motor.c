//
// Created by xiaosai on 3/15/2026.
//

#include "periph_motor.h"

#include <math.h>
#include <at32f403a_407_tmr.h>


void periph_motor1_set_pwm(const uint16_t u, const uint16_t v, const uint16_t w) {
    TMR1->c1dt = u;
    TMR1->c2dt = v;
    TMR1->c3dt = w;
}

void periph_motor2_set_pwm(const uint16_t u, const uint16_t v, const uint16_t w) {
    TMR8->c1dt = u;
    TMR8->c2dt = v;
    TMR8->c3dt = w;
}

float theta1 = 0.0f;
void periph_motor1_test(void) {
    theta1+=0.05f;
    if(theta1 > 6.283185f)
        theta1 -= 6.283185f;

    float u = sinf(theta1);
    float v = sinf(theta1 - 2.09439f);
    float w = sinf(theta1 + 2.09439f);

    uint16_t pwm_u = (uint16_t)((u * 0.05f + 0.5f) * 6000.0f);
    uint16_t pwm_v = (uint16_t)((v * 0.05f + 0.5f) * 6000.0f);
    uint16_t pwm_w = (uint16_t)((w * 0.05f + 0.5f) * 6000.0f);

    periph_motor1_set_pwm(pwm_u, pwm_v, pwm_w);
    // periph_motor_set_pwm(4000, 1000, 1000);
}

float theta2 = 0.0f;
void periph_motor2_test(void) {
    theta2+=0.05f;
    if(theta2 > 6.283185f)
        theta2 -= 6.283185f;

    float u = sinf(theta2);
    float v = sinf(theta2 - 2.09439f);
    float w = sinf(theta2 + 2.09439f);

    uint16_t pwm_u = (uint16_t)((u * 0.05f + 0.5f) * 6000.0f);
    uint16_t pwm_v = (uint16_t)((v * 0.05f + 0.5f) * 6000.0f);
    uint16_t pwm_w = (uint16_t)((w * 0.05f + 0.5f) * 6000.0f);

    periph_motor2_set_pwm(pwm_u, pwm_v, pwm_w);
    // periph_motor_set_pwm(4000, 1000, 1000);
}