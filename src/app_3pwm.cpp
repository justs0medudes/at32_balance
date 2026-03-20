//
// Created by xiaosai on 3/17/2026.
//

#include "app_3pwm.h"

#include <periph_encoder.h>

extern "C" {
#include "periph_motor.h"
#include "sys_gpio.h"
}


AT32Driver3PWM::AT32Driver3PWM(uint8_t id) {
    motor_id = id;
}

void AT32Driver3PWM::disable() {
    periph_motor_set_pwm(motor_id, 0, 0, 0);
    MOTOR_EN0;
}

void AT32Driver3PWM::enable() {
    MOTOR_EN1;
    periph_motor_set_pwm(motor_id, 0, 0, 0);
}

int AT32Driver3PWM::init() {
    // protection if voltage limit is bigger than power supply or not defined
    if (voltage_power_supply <= 0)
        voltage_power_supply = 12.0f;
    if (!_isset(voltage_limit) || voltage_limit > voltage_power_supply)
        voltage_limit =  voltage_power_supply;
    if (pwm_frequency <= 0)
        pwm_frequency = 20000;
    initialized = true;
    return 1;
}

void AT32Driver3PWM::setPwm(float Ua, float Ub, float Uc) {
    Ua = _constrain(Ua, 0.0f, voltage_limit);
    Ub = _constrain(Ub, 0.0f, voltage_limit);
    Uc = _constrain(Uc, 0.0f, voltage_limit);

    dc_a = _constrain(Ua / voltage_power_supply, 0.0f , 1.0f);
    dc_b = _constrain(Ub / voltage_power_supply, 0.0f , 1.0f);
    dc_c = _constrain(Uc / voltage_power_supply, 0.0f , 1.0f);

    uint16_t u = static_cast<uint16_t>(dc_a * 6000);
    uint16_t v = static_cast<uint16_t>(dc_b * 6000);
    uint16_t w = static_cast<uint16_t>(dc_c * 6000);

    periph_motor_set_pwm(motor_id, u, v, w);
}

void AT32Driver3PWM::setPhaseState(PhaseState sa, PhaseState sb, PhaseState sc) {
    uint16_t u = 0;
    uint16_t v = 0;
    uint16_t w = 0;

    if (motor_id == 1) {
        u = (sa == PHASE_ON) ? TMR1->c1dt : 0;
        v = (sb == PHASE_ON) ? TMR1->c2dt : 0;
        w = (sc == PHASE_ON) ? TMR1->c3dt : 0;
    } else if (motor_id == 2) {
        u = (sa == PHASE_ON) ? TMR8->c1dt : 0;
        v = (sb == PHASE_ON) ? TMR8->c2dt : 0;
        w = (sc == PHASE_ON) ? TMR8->c3dt : 0;
    }
    periph_motor_set_pwm(motor_id, u, v, w);
}

