//
// Created by xiaosai on 3/17/2026.
//

#ifndef AT32_BALANCE_V0_1_APP_3PWM_H
#define AT32_BALANCE_V0_1_APP_3PWM_H

#include <cstdint>

#include "../common/base_classes/BLDCDriver.h"
#include "../common/foc_utils.h"

class AT32Driver3PWM : public BLDCDriver {
    public:
        AT32Driver3PWM(uint8_t id);

        int init() override;

        void disable() override;
        void enable() override;

        void setPwm(float Ua, float Ub, float Uc) override;

        void setPhaseState(PhaseState sa, PhaseState sb, PhaseState sc) override;
    private:
        uint8_t motor_id;
};

#endif //AT32_BALANCE_V0_1_APP_3PWM_H