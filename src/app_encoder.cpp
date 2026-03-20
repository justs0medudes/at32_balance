//
// Created by xiaosai on 3/16/2026.
//

#include "app_encoder.h"

extern "C" {
#include "periph_encoder.h"
}

MA732Encoder::MA732Encoder(uint8_t id){
    // define all the necessary sensor variables
    // or leave empty if not necessary
    sensor_id = id;
    last = 0;
    if (id == 1) {
        angle_ptr = &ma732.encoder1.angle_rad;
        // vel_ptr = &ma732.encoder1.diff_rad;
    } else if (id == 2) {
        angle_ptr = &ma732.encoder2.angle_rad;
        // vel_ptr = &ma732.encoder2.diff_rad;
    }

}
void MA732Encoder::init(){
    // setup all the needed sensor hardware
    // for example
    periph_encoder_init();
}

float MA732Encoder::getSensorAngle(){
    // Get current shaft angle from the sensor hardware, and
    // return it as a float in radians, in the range 0 to 2PI.
    uint32_t now = micros();
    if ((now - last) > 0) {
        switch (sensor_id) {
            case 1: periph_encoder1_handle(); break;
            case 2: periph_encoder2_handle(); break;
            default: break;
        }
        last = now;
    }
    return *angle_ptr;
}

// float MA732Encoder::getVelocity() {
//     return *vel_ptr;
// }
