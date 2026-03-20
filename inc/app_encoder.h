//
// Created by xiaosai on 3/16/2026.
//

#pragma once

#include <SimpleFOC.h>
#include "../common/base_classes/Sensor.h"

class MA732Encoder: public Sensor{
    public:
        MA732Encoder(uint8_t id);

        // initialize the sensor hardware
        void init() override;

        // Get current shaft angle from the sensor hardware, and
        // return it as a float in radians, in the range 0 to 2PI.
        //  - This method is pure virtual and must be implemented in subclasses.
        //    Calling this method directly does not update the base-class internal fields.
        //    Use update() when calling from outside code.
        float getSensorAngle() override;
        // float getVelocity() override;
    private:
        float* angle_ptr;
        // float* vel_ptr;
        uint8_t sensor_id;
        uint32_t last;
};
